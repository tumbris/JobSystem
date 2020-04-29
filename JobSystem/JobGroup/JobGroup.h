#pragma once

#include <JobSystem/Job/GenericJob.h>
#include <JobSystem/JobSystemTypes.h>
#include <Utility/Ref/IntrusivePtr.h>
#include <queue>

class JobGroup : public Noncopyable
{
public:

    JobGroup(JobGroupPriority priority);
    virtual ~JobGroup() = default;

    void AddJob(IntrusivePtr<GenericJob> job);
    virtual bool ExecuteOneJob();

    JobGroupPriority GetPriority() const { return priority; }
    std::size_t Size() const;

protected:
    std::queue<IntrusivePtr<GenericJob>> jobs;
    JobGroupPriority priority;
};

namespace std
{
    template<>
    struct less<JobGroup>
    {
        constexpr bool operator()(const JobGroup& lhs, const JobGroup& rhs) const
        {
            return lhs.GetPriority() < rhs.GetPriority();
        }
    };
}