#pragma once

#include <JobSystem/JobGroup/JobGroup.h>
#include <map>

class Workload : public Noncopyable
{
public:
    Workload() = default;
    ~Workload() = default;

    void AddJob(IntrusivePtr<GenericJob> job, JobGroupPriority priority);
    void ExecuteOneJob();

private:
    std::map<JobGroupPriority, JobGroup> jobGroups;
};
