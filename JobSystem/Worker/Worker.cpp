#include "Worker.h"

Worker::Worker(WorkerAffinity affinity) 
    : workerThread(std::nullopt)
    , affinity(affinity)
{
    workerProcParams = new WorkerProcParams{ this, false };
    workerThread.emplace(&Worker::WorkerProc, workerProcParams);
    workerId = workerThread->get_id();
}

Worker::~Worker()
{
    workerProcParams->isDone.store(true);
    addJobNotifier.notify_all();

    if (workerThread.has_value())
    {
        workerThread->join();
    }
}

void Worker::Enqueue(IntrusivePtr<GenericJob> job, JobGroupPriority priority)
{
    mtx.lock();
    buffer.push({ job, priority });
    mtx.unlock();
    addJobNotifier.notify_all();
}

std::size_t Worker::GetJobsCountWithHigherPriority(JobGroupPriority priority)
{
    return primaryWorkload.GetJobsCountWithHigherPriority(priority);
}

void Worker::WorkerProc(WorkerProcParams* workerParams)
{
    using namespace std::chrono_literals;
    Worker& worker = *(workerParams->worker);

    while (!(workerParams->isDone.load()))
    {
        {
            std::unique_lock<std::mutex> ulock(worker.mtx);
            if (worker.primaryWorkload.Empty())
            {
                worker.addJobNotifier.wait(ulock, [&]() { return !(worker.buffer.empty()) || workerParams->isDone.load(); });
            }
            else
            {
                worker.addJobNotifier.wait_for(ulock, 0us, [&]() { return !(worker.buffer.empty()) || workerParams->isDone.load(); });
            }
            while (!(worker.buffer.empty()))
            {
                auto jobConfig = worker.buffer.front();
                worker.primaryWorkload.AddJob(jobConfig.first, jobConfig.second);
                worker.buffer.pop();
            }
        }
        worker.primaryWorkload.ExecuteOneJob();
    }
}

void Worker::Enqueue(const std::pair<IntrusivePtr<GenericJob>, JobGroupPriority>& jobConfig)
{
    Enqueue(jobConfig.first, jobConfig.second);
}
