#include "Workload.h"

void Workload::AddJob(IntrusivePtr<GenericJob> job, JobGroupPriority priority)
{
    jobGroups[priority].AddJob(job);
}

bool Workload::ExecuteOneJob()
{
    for (auto& group : jobGroups)
    {
        if (group.second.ExecuteOneJob())
        {
            return true;
        }
    }

    //workload empty and no jobs to be executed
    return false;
}

std::size_t Workload::GetJobsCountWithHigherPriority(JobGroupPriority priority)
{
    std::size_t res = 0;
    const auto found = jobGroups.find(priority);
    for (auto it = jobGroups.begin(); it != found; ++it)
    {
        res += it->second.Size();
    }
    if (found != jobGroups.end())
    {
        res += found->second.Size();
    }
    return res;
}
