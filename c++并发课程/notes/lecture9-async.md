# lectrue 9

## std::async  

std::async 是一个函数模板（在头文件\<future\>中），用来启动一个异步任务，启动后，返回一个std::future对象  
启动一个异步任务指的是"自动创建一个线程并开始执行对应的线程入口函数"，他返回一个std::future对象，这个对象里边就包含了线程入口函数所返回的结果，我们可以通过调用future对象的成员函数 **get()** 来获取结果  

### 函数作为std::async的入口函数  

语法如下：  

```c++
std::future<线程入口函数返回类型> result = std::async(线程入口函数); //创建一个线程并执行
std::cout << result.get() << std::endl;
```

示例如下：  

```c++
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

    /*输出
    main thread, thread_id = 1
    continue......!
    my_func() start, thread_id = 1
    sleeping......
    my_func() ends, thread_id = 1
    result is 5
    end...
    */
}
```

注意:  
get()函数只能调用一次，get函数的设计是用了移动语义  

### 类成员函数作为std::async的入口函数  

语法如下：  

```c++
std::future<线程入口函数返回类型> result = std::async(&类::成员函数, &类的实例, 类的成员函数的参数); //创建一个线程并执行
std::cout << result.get() << std::endl;
```

示例如下：  

```c++
class A
{
public:
    int my_func(int& param)
    {
        std::cout << "param is " << param << std::endl;
        param++;

        std::cout << "my_func() start, thread_id = " << std::this_thread::get_id() << std::endl;
        std::cout << "sleeping......" << std::endl;
        std::chrono::milliseconds dura(5000);
        std::this_thread::sleep_for(dura);

        std::cout << "my_func() ends, thread_id = " << std::this_thread::get_id() << std::endl;
        return 5;
    }
};


void test()
{
    A a;
    int param = 12;

    std::cout << "main thread, thread_id = " << std::this_thread::get_id() << std::endl;
    std::future<int> result = std::async(&A::my_func, &a, std::ref(param)); //创建一个线程并执行
    std::cout << "continue......!" << std::endl;

    std::cout << "result is " << result.get() << std::endl; //如果result.get()不返回，那么会阻塞在这儿
    std::cout << "main thread param is " << param << std::endl;
    std::cout << "end..." << std::endl; //result.get()返回后才会往下执行
    return;
    
    /*输出
    main thread, thread_id = 1
    continue......!
    param is 12
    my_func() start, thread_id = 1
    sleeping......
    my_func() ends, thread_id = 1
    result is 5
    main thread param is 13
    end...
    */
}
```

如果不想result.get()获取结果，也可以用result.wait()  

### std::async的其他参数  

我们额外向std::async传递一个参数，该参数类型是std::launch，它是枚举类型，从而达到一些特殊目的  

std::launch::deferred表示线程入口函数被延迟到std::future的wait或get函数调用时才执行。如果wait或者get在async后没有被调用，那么线程不会执行，实际上，线程没有被创建  

```c++
void my_thread()
{
    std::cout << "sub-thread begins, id =  " << std::this_thread::get_id() << std::endl;
    std::cout << "sub-thread ends, id =  " << std::this_thread::get_id() << std::endl;
}

void test()
{
    std::future<void> result = std::async(std::launch::deferred, my_thread);
    //注意没有result.wait();
    return;

    //没有输出
}
```

std::launch::async表示在调用async函数的时候就开始创建线程并执行（不需要get()或者wait()）。  

```c++
void my_thread()
{
    std::cout << "sub-thread begins, id =  " << std::this_thread::get_id() << std::endl;
    std::cout << "sub-thread ends, id =  " << std::this_thread::get_id() << std::endl;
}

void test()
{
    std::future<void> result = std::async(std::launch::async, my_thread);
    //注意没有result.wait();
    return;

    /*输出
    sub-thread begins, id =  2
    sub-thread ends, id =  2
    */
}
```

如果参数是std::launch::async | std::launch::deferred 意味着系统可能采用async可能采用deferred。具体哪个由系统决定。async函数默认使用的参数就是std::launch::async | std::launch::deferred  

## std::packaged_task  

std::packaged_task:打包任务，把任务包装起来。它是一个类模板，模板参数是各种可调用对象。示例如下：  

```c++
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
```

## std::promise  

std::promise也是类模板，示例如下，这个例子给出了一种简单的线程通信的形式：  

```c++
void mythread1(std::promise<int>& tmpp, int calc)
{
    std::chrono::milliseconds dura(2000);
    std::this_thread::sleep_for(dura);

    calc++;
    int result = calc;
    tmpp.set_value(result);

    return;
}

void mythread2(std::future<int>& tmpf)
{
    int result = tmpf.get();
    std::cout << "result is " << result << std::endl;
    return;
}

void test()
{
    std::promise<int> myprom; //声明一个std::promise对象，保存的值类型为int
    std::thread t1(mythread1, std::ref(myprom), 180);
    t1.join();

    std::future<int> f1 = myprom.get_future();
    //std::cout << f1.get() << std::endl; 
    //不能使用f1.get(),否则后面std::ref(f1)会出错，因为一旦std::future.get()被调用，它将变为无效，get函数的设计是用了移动语义

    std::thread t2(mythread2, std::ref(f1));
    t2.join();

    return;
}
```
