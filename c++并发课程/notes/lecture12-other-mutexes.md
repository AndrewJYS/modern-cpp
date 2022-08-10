# lecture 12  

## std::recursive_mutex  

std::mutex属于独占式互斥量，自己lock()之后别人无法lock();std::recursive_mutex (在头文件\<mutex\>中) 允许同一线程同一互斥量多次lock()，但是效率比std::mutex低一些。  

## std::timed_mutex, std::recursive_timed_mutex  

std::timed_mutex是带超时功能的独占互斥量。成员函数try_lock_for()，参数是一段时间，作用是等待一段时间，预估在这段时间内拿到锁。如果拿到锁，返回true，这时程序中不能忘记添加unlock()操作；如果这段时间没有拿到锁，返回false，程序就往下执行，不会阻塞  

```c++
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

void test()
{
    std::thread t1(my_thread1);
    std::thread t2(my_thread2);
    t1.join();
    t2.join();
    
    //输出：没有拿到锁

    return;
}
```

成员函数try_lock_until()参数是个未来的时间点，如果时间到了拿到了锁，返回true，拿到锁之后，程序不能忘记添加unlock()函数在需要的时候解锁。如果没有拿到锁，返回false，但不会阻塞  

```c++
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

void test2()
{
    std::thread t1(my_thread1);
    std::thread t3(my_thread3);
    t1.join();
    t3.join();

    //输出：没有拿到锁

    return;
}
```
