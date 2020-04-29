#include <Utility/Callback.h>
#include <Utility/Ref/IntrusivePtr.h>
#include <iostream>
#include <vector>

class A
{
public:
	int foo() { return 5; }
};

int main()
{
	A a;

	std::cout << Callback(&a, &A::foo)();
}