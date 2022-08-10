#include <iostream>
#include <mutex>
#include <thread>

std::timed_mutex t_mutex;

void my_thread1()
{
    t_mutex.lock();
    std::chrono::microseconds sleeptime(5000);
    std::this_thread::sleep_for(sleeptime);
    t_mutex.unlock();
}

void my_thread2()
{
    std::chrono::microseconds timeout(100);
    if (t_mutex.try_lock_for(timeout))
    {
        std::cout << "拿到了锁" << std::endl;
        t_mutex.unlock();
    }
    else
    {
        std::cout << "没有拿到锁" << std::endl;
    }
    return;
}

void my_thread3()
{
    std::chrono::microseconds timeout(100);
    if (t_mutex.try_lock_until(std::chrono::steady_clock::now() + timeout)) //等到当前时间的100ms后
    {
        std::cout << "拿到了锁" << std::endl;
        t_mutex.unlock();
    }
    else
    {
        std::cout << "没有拿到锁" << std::endl;
    }
    return;
}

void test1()
{
    std::thread t1(my_thread1);
    std::thread t2(my_thread2);
    t1.join();
    t2.join();

    //输出：没有拿到锁

    return;
}

void test2()
{
    std::thread t1(my_thread1);
    std::thread t3(my_thread3);
    t1.join();
    t3.join();

    //输出：没有拿到锁

    return;
}

int main()
{
    test1();
    test2();

    return 0;
}
