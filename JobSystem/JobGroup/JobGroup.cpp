#include <JobSystem/JobGroup/JobGroup.h>
#include <JobSystem/Job/GenericJob.h>

JobGroup::JobGroup(JobGroupPriority priority) : priority(priority) {}

void JobGroup::AddJob(IntrusivePtr<GenericJob> job)
{
    jobs.push(std::move(job));
}

void JobGroup::ExecuteOneJob()
{
    jobs.front()->Execute();
    jobs.pop();
}
