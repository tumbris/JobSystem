#include <JobSystem/Job/GenericJob.h>

void GenericJob::Execute()
{
#if !defined(NDEBUG)
	startedExecution = true;
#endif

	job();
}
