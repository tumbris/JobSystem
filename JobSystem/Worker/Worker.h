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

    Worker(Worker&&) = default;
    Worker& operator=(Worker&&) = default;

    void Enqueue(IntrusivePtr<GenericJob> job, JobGroupPriority priority);
    std::size_t GetJobsCountWithHigherPriority(JobGroupPriority priority);

    std::thread::id GetId() { return workerId; }
    WorkerAffinity GetAffinity() { return affinity; }

private:

    struct WorkerProcParams
    {
        WorkerProcParams(Worker* worker, bool isDone) : worker(worker), isDone(isDone) {}

        Worker* worker = nullptr;
        std::atomic_bool isDone = false;
    };

    static void WorkerProc(WorkerProcParams* workerParams);
    void Enqueue(const std::pair<IntrusivePtr<GenericJob>, JobGroupPriority>& jobConfig);
private:
    std::optional<std::thread> workerThread;

    Workload primaryWorkload;
    std::queue<std::pair<IntrusivePtr<GenericJob>, JobGroupPriority>> buffer;

    std::mutex mtx;
    std::condition_variable addJobNotifier;

    WorkerProcParams* workerProcParams;
    
    std::thread::id workerId;
    WorkerAffinity affinity;
};