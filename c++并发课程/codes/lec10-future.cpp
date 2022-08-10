#include <iostream>
#include <thread>
#include <future>

int my_func()
{
    std::chrono::milliseconds dura(5000);
    std::this_thread::sleep_for(dura);
    return 5;
}

void test()
{
    std::future<int> result = std::async(std::launch::async, my_func); //创建一个线程并执行
    std::future_status status = result.wait_for(std::chrono::milliseconds(1000)); // 等待1s，希望子线程返回

    if (status == std::future_status::ready)
	{
		std::cout << "子线程执行完" << std::endl;
		std::cout << result.get() << std::endl;
	}
	else if (status == std::future_status::timeout)
	{
		std::cout << "子线程没有执行完，超时" << std::endl;
	}
	else if (status == std::future_status::deferred)
	{
	    //async第一个参数被设置为std::launch::deferred，就会显示延迟
		std::cout << "线程延迟执行" << std::endl;
		std::cout << result.get() << std::endl;
	}

    return;

	/*
    std::future<int> result = std::async(std::launch::async, my_func);
    std::future_status status = result.wait_for(std::chrono::milliseconds(1000));

    子线程没有执行完，超时


    std::future<int> result = std::async(std::launch::async, my_func);
    std::future_status status = result.wait_for(std::chrono::milliseconds(6000));

    子线程执行完
    5


    std::future<int> result = std::async(std::launch::deferred, my_func);
    std::future_status status = result.wait_for(std::chrono::milliseconds(1000));

    线程延迟执行
    5

    */
}

int main()
{
    test();

    return 0;
}
