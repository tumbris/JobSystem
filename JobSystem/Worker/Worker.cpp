#include "Worker.h"

Worker::Worker(WorkerAffinity affinity) 
    : workerThread(std::nullopt)
    , affinity(affinity)
{
    workerProcParams = std::make_shared<WorkerProcParams>(this, false);
    workerThread.emplace(&Worker::WorkerProc, workerProcParams);
    workerId = workerThread->get_id();
}

Worker::~Worker()
{
    workerProcParams->isDone.store(true);

    if (workerThread.has_value())
    {
        workerThread->join();
    }
}

void Worker::AddJob(IntrusivePtr<GenericJob> job, JobGroupPriority priority)
{
    mtx.lock();
    buffer.push(job);
    mtx.unlock();
    addJobNotifier.notify_all();
}

std::size_t Worker::GetJobsCountWithHigherPriority(JobGroupPriority priority)
{
    return primaryWorkload.GetJobsCountWithHigherPriority(priority);
}

void Worker::WorkerProc(std::shared_ptr<WorkerProcParams> workerParams)
{
    while (workerParams->isDone.load())
    {
        Worker& worker = *(workerParams->worker);
        {
            std::unique_lock<std::mutex> ulock;
            while (!(worker.buffer.empty()))
            {
                worker.addJobNotifier.wait(ulock);
            }
            while (!(worker.buffer.empty()))
            {
                worker.AddJob(worker.buffer.front());
                worker.buffer.pop();
            }
        }

        bool hadJob = true;
        do
        {
            hadJob = worker.primaryWorkload.ExecuteOneJob();
        } while (hadJob);
    }
}
