#include <iostream>

template<typename T>
T foo(T*)
{
	//
	std::cout << __func__ << std::endl;
}
