#include <iostream>
#include <vector>
#include <thread>

void do_work(int i)
{
	printf("thread %d do work\n", i);
}

void f()
{
	std::vector<std::thread> my_threads;
	for (int i = 0; i < 1000; i++)
	{
		my_threads.emplace_back(do_work, i);
	}
	for (auto& t : my_threads)
	{
		t.join();
	}
}

int main()
{
	f();

	return 0;
}