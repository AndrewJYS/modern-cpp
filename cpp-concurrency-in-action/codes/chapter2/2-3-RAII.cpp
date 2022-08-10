#include <iostream>
#include <thread>


void do_something(int i)
{
	std::cout << "do something " << i << '\n';
}

void do_something_in_current_thread()
{
	for (int i = 0; i < 10000; ++i)
	{
		std::cout << "do somthing in current thread " << i << '\n';
	}
}

struct func
{
	int& i;
	func(int& i_) : i(i_) {}
	void operator()()
	{
		for (int j = 0; j < 10000; ++j)
		{
			do_something(i);
		}
	}
};

class thread_guard
{
private:
	std::thread& t;

public:
	explicit thread_guard(std::thread& t_) : t(t_) {}
	~thread_guard()
	{
		if (t.joinable())
		{
			t.join();
		}
	}

	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
};

void f()
{
	int state = 0;
	func my_func(state);
	std::thread t(my_func);
	thread_guard g(t);
	do_something_in_current_thread();
}

int main()
{
	f();

	return 0;
}