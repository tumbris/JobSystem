#pragma once

#include <JobSystem/Worker/Worker.h>

class WorkerPool : public Noncopyable
{
public:
    struct CreateParams
    {
        std::vector<WorkerAffinity> affinities;
    };
private:
    WorkerPool(const CreateParams& params);
public:
    static void CreateInstance(const CreateParams& params);
    static WorkerPool* GetInstance();
    static void DeleteInstance();

    void Enqueue(IntrusivePtr<GenericJob> job, JobGroupPriority priority = JobGroupDefaultPriority);

private:
    std::map<std::thread::id, std::unique_ptr<Worker>> workers;

private:
    static WorkerPool* instance;
};

