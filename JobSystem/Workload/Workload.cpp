#include "Workload.h"

void Workload::AddJob(IntrusivePtr<GenericJob> job, JobGroupPriority priority)
{
    jobGroups[priority].AddJob(job);
}

void Workload::ExecuteOneJob()
{
    for (auto& group : jobGroups)
    {
        if (group.second.ExecuteOneJob())
        {
            return;
        }
    }
}
