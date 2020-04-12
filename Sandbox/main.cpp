#include <Utility/Ref/IntrusivePtr.h>
#include <iostream>
#include <vector>

class A : public ReferenceCountable<>
{

};

int main()
{
	auto ptr = MakeIntrusive<A>();

	auto b = ptr;

	{
		IntrusivePtr<A> c;
		c = b;
		c = std::move(b);
	}
	std::cout << "Hello, World!\n";
}