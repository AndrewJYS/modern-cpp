# lecture 6: unique_lock  

## unique_lock()的第二参数  

一般情况下，std::lock_guard就可以应付大量的问题（它取代了mutex的lock()和unlock()函数），unique_lock()比lock_guard更加灵活，但效率差一点  

和std::lock_guard一样，unique_lock可以接受第二个参数，下面介绍几种它的第二参数  

### std::adopt_lock  

这种参数的用法和std::lock_guard中一样，作用也相同  
std::adopt_lock表示这个互斥量已经被提前lock了（**在std:::adopt_lock之前一定要先把互斥量加锁，否则会报错**）  
adopt_lock的效果是“假设调用方 线程已经拥有了互斥量的所有权，即mutex::lock()调用成功”，通知std::unique_lock或std::lock_guard不需要在构造函数中lock这个互斥量了  

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

            std::lock(my_mutex1, my_mutex2);
            std::unique_lock<mutex> u1(my_mutex1, std::adopt_lock);
            std::unique_lock<mutex> u2(my_mutex2, std::adopt_lock);

            msgRecvQueue.push_back(i);
        }
    }

    bool outMsg(int& command)
    {
        std::lock(my_mutex1, my_mutex2);

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
    std::mutex my_mutex1;
    std::mutex my_mutex2;
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

### std::try_to_lock  

下面这个示例中，有两个线程，其中一个线程在加锁之后sleep，那么另一个线程拿不到锁，就会阻塞，进入长时间等待。  

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

            my_mutex1.lock();
            std::unique_lock<mutex> u1(my_mutex1, std::adopt_lock);

            msgRecvQueue.push_back(i);
        }
    }

    bool outMsg(int& command)
    {
        std::unique_lock<mutex> u1(my_mutex1);

        std::chrono::milliseconds duration(20000); // 20000毫秒
        std::this_thread::sleep_for(duration); //睡眠20000毫秒

        if (!msgRecvQueue.empty())
        {
            command = msgRecvQueue.front();
            msgRecvQueue.pop_front();
            return true;
        }
        return false;
    }

    //抽取消息处理
    void outMsgRecvQueue() {......}
    ......
};

void test1() {......}
```

为了让另一个线程拿不到锁的情况下，不进入等待，而是能做些什么，我们引入std::try_to_lock参数。使用该参数时，会尝试用mutex::lock()函数锁定该互斥量，但如果没有锁定成功，就会立即返回，并不会阻塞。**用std::try_to_lock的前提是：不能先使用mutex::lock()函数**（因为前面已经说了，std::try_to_lock会尝试使用mutex::lock(),同一个互斥量对象两次使用mutex::lock()会卡死）

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

            std::unique_lock<mutex> u1(my_mutex1, std::try_to_lock);
            if (u1.owns_lock())
            {
                //拿到了锁
                msgRecvQueue.push_back(i);
            }
            else
            {
                //没拿到锁
                cout << "do not own lock, do something else" << endl;
            }
        }
    }
    ......//同上
};
```

### std::defer_lock  

用std::defer_lock的前提是不能先对互斥量用mutex::lock()，否则会报错。std::defer_lock会初始化一个没有加锁的互斥量。std::defer_lock会配合一些std::unique_lock的成员函数使用，比如std::unique_lock.lock()和std::unique_lock.unlock()，下面一节将详细介绍  

## std::unique_lock的成员函数  

### std::unique_lock.lock()  

下面的例子是std::defer_lock和std::unique_lock.lock()配合使用，但不需要添加unlock，因为函数退出时，会自动解锁  

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

            std::unique_lock<mutex> u1(my_mutex1, std::defer_lock);
            u1.lock();
            
            msgRecvQueue.push_back(i);
        }
    }

    ......//同上
};
```

### std::unique_lock.unlock()  

为了提高灵活性，在函数退出前，完成一些对非共享代码的处理（也就是需要提前解锁），可以配合std::unique_lock.unlock()使用；若处理完之后，有需要保护一些代码，此时，可以再次使用std::unique_lock.lock()。示例如下：  

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

            std::unique_lock<mutex> u1(my_mutex1, std::defer_lock);
            u1.lock();
            msgRecvQueue.push_back(i);
            u1.unlock();
            
            //......处理其他代码
            
            u1.lock();
        }
    }

    //......
};
```

### std::unique_lock::try_lock()  

std::defer_lock还可以和std::unique_lock::try_lock()配合使用，效果与之前的std::try_to_lock参数类似。std::unique_lock::try_lock()会尝试加锁，如果成功则返回true，否则返回false  

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

            std::unique_lock<mutex> u1(my_mutex1, std::defer_lock);

            if (u1.try_lock() == true) //返回true表示 拿到锁
            {
                //拿到了锁
                msgRecvQueue.push_back(i);
            }
            else
            {
                //没拿到锁
                cout << "do not own lock, do something else" << endl;
            }
        }
    }

    ......//同上
};
```

### std::unique_lock.release()  

release()返回它所管理的mutex对象指针，并释放所有权，也就是说，这个unique_lock和mutex不再有关系。如果mutex此时是加锁状态，我们不能忘记后续对其解锁  

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

            std::unique_lock<mutex> u1(my_mutex1);
            msgRecvQueue.push_back(i);

            std::mutex* p_mutex = u1.release();
            p_mutex->unlock();
        }
    }

    ......//同上
};
```

**注意：**  
一定要用mutex的指针接受release返回的指针，然后在对指针操作，下面代码是错误的，因为此时u1已经和mutex没有关联了，而锁是加在mutex上的，所以要对mutex进行操作  

```c++
std::unique_lock<mutex> u1(my_mutex1);
msgRecvQueue.push_back(i);

u1.release();
u1.unlock();
```

## std::unique_lock所有权的传递  

