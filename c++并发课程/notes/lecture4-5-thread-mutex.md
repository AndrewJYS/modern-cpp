# lecture4-5: Thread Mutex  

## 多线程示例  

```c++
void my_print(int num)
{
    cout << "my_print开始执行，线程编号：" << num << '\n';

    cout << "my_print结束执行，线程编号：" << num << '\n' ;
    return;
}

void test1()
{
    vector<thread> my_threads;
    for (int i = 0; i < 5; ++i)
    {
        my_threads.push_back(thread(my_print, i)); //创建并开始执行线程
    }
    for (auto it = my_threads.begin(); it != my_threads.end(); ++it)
    {
        it->join();
    }
    cout << "主线程运行结束" << endl;

    /*
    my_print开始执行，线程编号：my_print开始执行，线程编号：1
    my_print结束执行，线程编号：1
    my_print开始执行，线程编号：3
    my_print结束执行，线程编号：3
    my_print开始执行，线程编号：2
    my_print结束执行，线程编号：2
    my_print开始执行，线程编号：4
    my_print结束执行，线程编号：4
    0
    my_print结束执行，线程编号：0
    主线程运行结束
    */
}
```

## mutex的使用  

这里，互斥量是一个类对象，多个线程尝试用lock()成员函数加锁，但只有一个线程能锁定成功（成功标识是lock()返回），如果没有成功，那么流程卡在lock()这里不断地尝试加锁。  
保护数据要不多不少。少了就没达到效果，多了就会影响效率  

用法：  
先lock(),操作共享数据，然后unlock()  
lock()和unlock()必须成对使用  

```c++
#define TOTAL 10000

class A
{
public:
    // 收取消息
    void inMsgRecvQueue()
    {
        for (int i = 0; i < TOTAL; ++i)
        {
            cout << "inMsgRecvQueue()执行，插入一个元素" << i << endl;

            my_mutex.lock();
            msgRecvQueue.push_back(i);
            my_mutex.unlock();
        }
    }

    bool outMsg(int& command)
    {
        my_mutex.lock();
        if (!msgRecvQueue.empty())
        {
            command = msgRecvQueue.front();
            msgRecvQueue.pop_front();
            my_mutex.unlock();
            return true;
        }

        my_mutex.unlock();
        return false;
    }

    //抽取消息处理
    void outMsgRecvQueue()
    {
        int command = 0;
        for (int i = 0; i < TOTAL; ++i)
        {
            bool result = outMsg(command);
            if (result)
            {
                cout << "outMsgRecvQueue()执行，取出一个元素" << command << endl;
            }
            else
            {
                cout << "outMsgRecvQueue()执行，但是列表为空" << endl;
            }
        }
        cout << "end" << endl;
    }
private:
    std::list<int> msgRecvQueue;
    std::mutex my_mutex;
};

void test1()
{
    A obj_a;
    std::thread out_thread(&A::outMsgRecvQueue, &obj_a);
    std::thread in_thread(&A::inMsgRecvQueue, &obj_a);
    out_thread.join();
    in_thread.join();
}
```

为了防止写了lock()但是忘记unlock()的情况，引入了std::lock_guard，可以取代lock()和unlock()  

```c++
class A
{
public:
    // ......同上

    bool outMsg(int& command)
    {
        std::lock_guard<std::mutex> guard(my_mutex);
        // lock_guard构造函数中执行了mutex::lock()函数
        // 在推出函数时，会调用lock_guard的析构函数，内含mutex::unlock()函数

        if (!msgRecvQueue.empty())
        {
            command = msgRecvQueue.front();
            msgRecvQueue.pop_front();
            return true;
        }
        return false;
    }

    ......
};
```

## 死锁  

常见的死锁示例如下：在两个线程中，共同拥有两把锁，但在两个线程中，这两把锁的加锁顺序刚好相反  

```c++
#define TOTAL 10000

class A
{
public:
    // 收取消息
    void inMsgRecvQueue()
    {
        for (int i = 0; i < TOTAL; ++i)
        {
            cout << "inMsgRecvQueue()执行，插入一个元素" << i << endl;

            my_mutex1.lock(); //先1后2
            my_mutex2.lock();
            msgRecvQueue.push_back(i);
            my_mutex2.unlock();
            my_mutex1.unlock();
        }
    }

    bool outMsg(int& command)
    {
        my_mutex2.lock(); //先2后1
        my_mutex1.lock();

        if (!msgRecvQueue.empty())
        {
            command = msgRecvQueue.front();
            msgRecvQueue.pop_front();
            my_mutex1.unlock();
            my_mutex2.unlock();
            return true;
        }

        my_mutex1.unlock();
        my_mutex2.unlock();
        return false;
    }

    //抽取消息处理
    void outMsgRecvQueue()
    {
        ......   
    }

private:
    std::list<int> msgRecvQueue;
    std::mutex my_mutex1;
    std::mutex my_mutex2;
};

void test1() {......}
```

一种简单的解决办法是在两个线程中使用相同的加锁顺序  

## std::lock()模板  

在处理多个互斥量的时候，可以使用std::lock()。它可以一次性锁住多个互斥量（至少两个，一个不行）；它不存在因为锁的顺序问题带来的死锁风险。std::lock()可以实现：如果互斥量中有一个没锁住，它就等着，直到所有互斥量都锁柱，再往下运行。要么都锁住，要么都不锁住，如果只有一个锁住，其他没有加锁成功，则立即把已经锁住的解锁  

基本用法：  

```c++
std::lock(mutex1, mutex2, ...);
... //需要保护的代码
mutex1.unlock();
mutex2.unlock();
...
```

示例如下：  

```c++
class A
{
public:
    // 收取消息
    void inMsgRecvQueue()
    {
        for (int i = 0; i < TOTAL; ++i)
        {
            cout << "inMsgRecvQueue()执行，插入一个元素" << i << endl;

            std::lock(my_mutex1, my_mutex2);
            msgRecvQueue.push_back(i);
            my_mutex2.unlock(); //解锁
            my_mutex1.unlock();
        }
    }

    bool outMsg(int& command)
    {
        std::lock(my_mutex1, my_mutex2);
        ......
    }
    ......
};
```

## std::adopt_lock  

从上述代码发现，使用std::lock()之后，可能容易忘记最后的unlock()，因此引入std::adopt_lock。用法如下：  

```c++
class A
{
public:
    // 收取消息
    void inMsgRecvQueue()
    {
        for (int i = 0; i < TOTAL; ++i)
        {
            cout << "inMsgRecvQueue()执行，插入一个元素" << i << endl;

            std::lock(my_mutex1, my_mutex2);
            std::lock_guard<std::mutex> guard1(my_mutex1, std::adopt_lock);
            std::lock_guard<std::mutex> guard2(my_mutex2, std::adopt_lock);
            // std::adopt_lock具体说明见lecture6开头的笔记

            msgRecvQueue.push_back(i);
        }
    }

    ......
};
```
