#include <JobSystem/Worker/WorkerPool.h>
#include <iostream>

int main()
{
    std::vector<WorkerAffinity> affinities(std::thread::hardware_concurrency(), 0);
    WorkerPool::CreateInstance({ affinities });

    auto job = new GenericJob([]()
        {
            std::cout << "Hui\n";
        });
    job->Then([](GenericJob* prev)
        {
            std::cout << "Hui has been printed!\n";
        });

    WorkerPool::GetInstance()->Enqueue(job);

    WorkerPool::DeleteInstance();
}