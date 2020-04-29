#include <JobSystem/JobGroup/JobGroup.h>
#include <JobSystem/Job/GenericJob.h>

JobGroup::JobGroup(JobGroupPriority priority) : priority(priority) {}

void JobGroup::AddJob(IntrusivePtr<GenericJob> job)
{
    jobs.push(std::move(job));
}

bool JobGroup::ExecuteOneJob()
{
    if (!jobs.empty())
    {
        jobs.front()->Execute();
        jobs.pop();
        return true;
    }
    return false;
}
