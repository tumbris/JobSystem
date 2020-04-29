#pragma once

#include <JobSystem/Job/GenericJob.h>
#include <JobSystem/JobSystemTypes.h>
#include <Utility/Ref/IntrusivePtr.h>
#include <queue>

class JobGroup
{
public:

    JobGroup(JobGroupPriority priority);
    virtual ~JobGroup() = default;

    void AddJob(IntrusivePtr<GenericJob> job);
    void ExecuteOneJob();

    JobGroupPriority GetPriority() { return priority; }

private:
    std::queue<IntrusivePtr<GenericJob>> jobs;
    JobGroupPriority priority;
};