#include <iostream>
#include <thread>

void my_func(int& i)
{
	i = 100;
}

void f()
{
	int state = 0;
	std::thread my_thread(my_func, std::ref(state));
	my_thread.join();
	std::cout << state << std::endl;
}

int main()
{
	f();

	return 0;
}