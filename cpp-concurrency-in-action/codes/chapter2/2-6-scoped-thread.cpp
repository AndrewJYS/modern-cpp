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

class Scoped_Thread
{
private:
	std::thread t;

public:
	explicit Scoped_Thread(std::thread t_) : t(std::move(t_))
	{
		if (!t.joinable())
		{
			throw std::logic_error("no thread");
		}
	}

	~Scoped_Thread()
	{
		t.join();
	}

	Scoped_Thread(Scoped_Thread const&) = delete;
	Scoped_Thread& operator=(Scoped_Thread const&) = delete;
};

void f()
{
	int state = 0;
	Scoped_Thread t(std::thread(func(state)));
	do_something_in_current_thread();
}

int main()
{
	f();

	return 0;
}