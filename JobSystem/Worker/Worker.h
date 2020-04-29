#pragma once

#include <JobSystem/Workload/Workload.h>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <optional>
#include <queue>
#include <memory>

class Worker : public Noncopyable
{
public:
    Worker(WorkerAffinity affinity);
    ~Worker();

    void AddJob(IntrusivePtr<GenericJob> job, JobGroupPriority priority);
    std::size_t GetJobsCountWithHigherPriority(JobGroupPriority priority);

    std::thread::id GetId() { return workerId; }
    WorkerAffinity GetAffinity() { return affinity; }

private:

    struct WorkerProcParams
    {
        Worker* worker = nullptr;
        std::atomic_bool isDone = false;
    };

    static void WorkerProc(std::shared_ptr<WorkerProcParams> workerParams);
private:
    std::optional<std::thread> workerThread;

    Workload primaryWorkload;
    std::queue<IntrusivePtr<GenericJob>> buffer;

    std::mutex mtx;
    std::condition_variable addJobNotifier;

    std::shared_ptr<WorkerProcParams> workerProcParams;

    std::thread::id workerId;
    WorkerAffinity affinity;
};