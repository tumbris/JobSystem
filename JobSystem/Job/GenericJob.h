#pragma once

#include <Utility/Ref/IntrusivePtr.h>
#include <Utility/Noncopyable.h>
#include <functional>
#include <cassert>

///////////////////////////////////////////////////////////////////////////////////
/////////////////////USE THIS CLASS ONLY OWNED BY INTRUSIVEPTR/////////////////////
class GenericJob : public ReferenceCountable<ThreadSafePolicy>, public Noncopyable
{
public:
    template <class Fn>
    GenericJob(Fn&& job) : job(std::forward<Fn>(job)) {}
    virtual ~GenericJob() = default;

    void Execute();

    template <class Fn>
    GenericJob& Then(Fn&& then);

private:
    std::function<void()> job;

#if !defined(NDEBUG)
    bool startedExecution = false;
#endif
};

template<class Fn>
GenericJob& GenericJob::Then(Fn&& then)
{
    assert(!startedExecution);
    job = [prev = std::move(job),
           thisPtr = IntrusivePtr(this),
           next = std::forward<Fn>(then)]()
    {
        prev();
        then(*thisPtr);
    };
    return *this;
}