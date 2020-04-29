#pragma once
#include <functional>

template <class Ret, class Obj, class... Args>
std::function<Ret(Args...)> Callback(Obj* object, Ret (Obj::*mem_fn)(Args...))
{
    return [=](Args... args) -> Ret { return (object->*mem_fn)(args...); };
}