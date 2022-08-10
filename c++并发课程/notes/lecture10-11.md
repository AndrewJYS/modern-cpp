# lecture 10-11  

## 枚举类型std::future_status  

std::future_status配合std::future使用，示例如下：  

```c++
int my_func()
{
    std::chrono::milliseconds dura(5000);
    return 5;
}

void test()
{
    std::future<int> result = std::async(std::launch::async, my_func); //创建一个线程并立即执行
    std::future_status status = result.wait_for(std::chrono::milliseconds(1000)); // 等待1s，希望子线程返回

    if (status == std::future_status::ready)
    {
        std::cout << "子线程执行完" << std::endl;
    }
    else if (status == std::future_status::timeout)
    {
        std::cout << "子线程没有执行完，超时" << std::endl;
        std::cout << result.get() << std::endl;
    }
    else if (status == std::future_status::deferred)
    {
        //async第一个参数被设置为std::launch::deferred，就会显示延迟
        std::cout << "线程延迟执行" << std::endl;
        std::cout << result.get() << std::endl;
    }

    return;
}
```

上述代码内含三种情况，代码和输出分别如下：  

```c++
std::future<int> result = std::async(std::launch::async, my_func);
std::future_status status = result.wait_for(std::chrono::milliseconds(1000));

//子线程没有执行完，超时


std::future<int> result = std::async(std::launch::async, my_func);
std::future_status status = result.wait_for(std::chrono::milliseconds(6000));

//子线程执行完
//5


std::future<int> result = std::async(std::launch::deferred, my_func);
std::future_status status = result.wait_for(std::chrono::milliseconds(1000));

//线程延迟执行
//5
```

## std::shared_future  

std::shared_future和future一样，也是个类模板。它为了解决future对象的get（）成员函数只能被调用一次的问题（假如有多个线程想要获取某线程中future包含的结果，那么不能多次调用get()，因为get()使用了移动语义）。  

下面的例子表明std::shared_future.get()可以调用多次  

```c++
int my_func()
{
    return 5;
}

void test()
{
    std::future<int> result = std::async(std::launch::async, my_func); //创建一个线程并执行
    std::shared_future<int> shared_result(std::move(result)); //此时result为空
    std::cout << shared_result.get() << std::endl; // 5
    std::cout << shared_result.get() << std::endl; // 5


    
    std::shared_future<int> shared_result2 = std::async(std::launch::async, my_func);
    std::cout << shared_result2.get() << std::endl;
    std::cout << shared_result2.get() << std::endl;
}
```

## 原子操作std::atomic  

原子操作是不需要用到互斥量加锁技术的并发编程方式。它在多线程中不会被打断，比互斥量效率更高。互斥量加锁一般针对的是一个代码段，而原子操作针对的一般是一个变量。  

std::atomic是一个类模板，是用来封装某个类型的值的  

```c++
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
```

**注意**  
std::atomic一般只针对++，--，+=，-=，&=，|=，^=运算符支持与原子操作。下面的代码中，不支持原子操作  

```c++
//把上述代码中void my_thread()的g_cnt++;改成
g_cnt = g_cnt + 1; //出错
```

## std::async和std:::thread的区别  

std::thread()创建线程；如果系统资源紧张，那么std::thread()创建线程可能会失败，那么执行std::thread()的整个程序可能崩溃；并且想要拿到线程入口函数的返回值，也不容易。  

std::async()是创建异步任务，可能创建线程也可能不创建线程，可以指定；并且可以通过future获取线程入口函数的返回值。特别的，当系统资源紧张，那么不加std::launch参数的std::async()调用不会创建新线程（系统会使用std::launch::deferred参数），当后续使用get()调用时，再创建运行  
