#include <JobSystem/Worker/WorkerPool.h>
#include <cassert>

WorkerPool* WorkerPool::instance = nullptr;

WorkerPool::WorkerPool(const CreateParams& params)
{
    assert(params.affinities.size() == std::thread::hardware_concurrency());
    for (std::size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
    {
        auto worker = std::make_unique<Worker>(params.affinities[i]);
        auto id = worker->GetId();
        workers.emplace(id, std::move(worker));
    }
}

void WorkerPool::CreateInstance(const CreateParams& params)
{
    instance = new (std::nothrow) WorkerPool(params);
}

WorkerPool* WorkerPool::GetInstance()
{
    return instance;
}

void WorkerPool::DeleteInstance()
{
    delete instance;
}

void WorkerPool::Enqueue(IntrusivePtr<GenericJob> job, JobGroupPriority priority)
{
    auto fit = std::min_element(workers.begin(), workers.end(),
        [&](const auto& a, const auto& b)
        {
            return a.second->GetJobsCountWithHigherPriority(priority) < b.second->GetJobsCountWithHigherPriority(priority);
        });
    if (fit != workers.end())
    {
        fit->second->Enqueue(job, priority);
    }
}
