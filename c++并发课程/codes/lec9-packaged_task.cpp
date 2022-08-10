#include <iostream>
#include <thread>
#include <future>

int my_func(int param)
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

    int param = 1;
    std::packaged_task<int(int)> mypt(my_func);
    std::thread t1(std::ref(mypt), param);
    t1.join();
    std::future<int> result = mypt.get_future();
    std::cout << result.get() << std::endl;

    /*输出
    main thread, thread_id = 1
    my_func() start, thread_id = 2
    sleeping......
    my_func() ends, thread_id = 2
    5
    */
}

int main()
{
    test();

    return 0;
}
