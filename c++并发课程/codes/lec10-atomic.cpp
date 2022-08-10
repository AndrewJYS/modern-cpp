#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> g_cnt {0};

void my_thread()
{
    for (int i = 0; i < 10000000; ++i)
    {
        g_cnt++; //对应的是原子操作，不会被打断
    }
    return;
}

void test()
{
    std::thread t1(my_thread);
    std::thread t2(my_thread);
    t1.join();
    t2.join();
    std::cout << g_cnt << std::endl;
}

int main()
{
    test();

    return 0;
}
