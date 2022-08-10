#include <iostream>
#include <thread>
#include <future>

int my_func()
{
    std::cout << "my_func() start, thread_id = " << std::this_thread::get_id() << std::endl;
    std::cout << "sleeping......" << std::endl;
    std::chrono::milliseconds dura(2000);
    std::this_thread::sleep_for(dura);
    std::cout << "my_func() ends, thread_id = " << std::this_thread::get_id() << std::endl;
    return 5;
}

void test()
{
    std::cout << "main thread, thread_id = " << std::this_thread::get_id() << std::endl;
    std::future<int> result = std::async(my_func); //创建一个线程并执行
    std::cout << "continue......!" << std::endl;

    std::cout << "result is " << result.get() << std::endl; //如果result.get()不返回，那么会阻塞在这儿
    std::cout << "end..." << std::endl; //result.get()返回后才会往下执行
    return;
}

int main()
{
    test();

    return 0;
}
