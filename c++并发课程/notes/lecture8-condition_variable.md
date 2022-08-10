# lecture 8  

## std::condition_variable  

std::condition_variable是一个类，需要引入头文件\<condition_variable\>，它等待一个条件达成。这个类需要互斥量来配合工作。我们仍然以第6课的代码为例子，在此基础上修改。有两个线程，线程A往命令队列中插入命令，线程B从命令队列中读取命令。当命令队列为空时，线程B阻塞，当命令队列被插入命令后，线程A唤醒线程B  

具体的调用逻辑在代码注释中给出  

### notify_one()  

```c++
#include <iostream>
#include <mutex>
#include <thread>
#include <list>
#include <condition_variable>
using namespace std;

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

            //假如outMsgRecvQueue()正在处理一个事务，需要一段时间，而不是正好卡在wait()那里等你唤醒
                //那么此时这个notify_one()就可能没有作用
            my_cond.notify_one(); //尝试把wait()的线程唤醒
        }
    }

    //抽取消息处理
    void outMsgRecvQueue()
    {
        int command = 0;

        while (true)
        {
            std::unique_lock<std::mutex> guard(my_mutex1);

            //wait()用来等条件成立，我们以lambda表达式为例考察wait()的机制

            //如果第二个参数lambda表达式的返回值是false，那么wait()将解锁互斥量，并阻塞到本行
                //直到别的线程调用notify_one()成员函数为止
            //如果没有第二个参数，情况同第二个参数是lambda表达式的返回值是false
            //如果第二个参数lambda表达式的返回值是true，wait()直接返回，程序向下运行

            //当其他线程用notify_one()把本线程唤醒后
            //wait()不断地尝试重新获取互斥量锁
            //(a) wait()会重复上述判断操作，如果获取不到，那么流程就卡在wait这里等着获取，如果获取到了，wait就继续执行(b)
            //(b) 此时获取到了锁（也就是对mutex上锁）
                //b.1) 如果wait()第二个参数lambda表达式的返回值是false，wait再次解锁，阻塞，等待被notify_one()唤醒
                //b.2) 如果wait()第二个参数lambda表达式的返回值是true，流程走下来
                //b.3) 如果没有第二个参数，流程走下来
            my_cond.wait(guard, [this] {
                if (!msgRecvQueue.empty())
                    return true;
                return false;
            });

            command = msgRecvQueue.front();
            msgRecvQueue.pop_front();
            guard.unlock();

            cout << "outMsgRecvQueue()执行，取出一个元素" << command << '\n' ;
        }

        cout << "end" << endl;
    }

private:
    std::list<int> msgRecvQueue;
    std::mutex my_mutex1;
    std::condition_variable my_cond;
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

**注意**  
如果msgRecvQueue列表中是空的，但读取线程被唤醒，这时称为虚假唤醒，为了避免这种情况，我们必须在wait()函数中加上（如上所示）第二个参数，即lambda表达式进行判断  

### notify_all()  

对上面的例程稍加修改，就可以测试notify_all()  

```c++
//将类中inMsgRecvQueue()函数的my_cond.notify_one();修改成下面的语句
my_cond.notify_all();

//将void test1()修改成下述代码
void test1()
{
    A obj_a;

    std::thread out_thread1(&A::outMsgRecvQueue, &obj_a);
    std::thread out_thread2(&A::outMsgRecvQueue, &obj_a);
    std::thread in_thread(&A::inMsgRecvQueue, &obj_a);

    out_thread1.join();
    out_thread2.join();
    in_thread.join();
}
```

### 总结  

notify_one()只唤醒一个线程，所以不存在锁争用，所以能够立即获得锁。其余的线程不会被唤醒，等待再次调用notify_one()或者notify_all()。  

notify_all()唤醒所有阻塞的线程，存在锁争用，只有一个线程能够获得锁。其余未获取锁的线程会阻塞，等待操作系统在互斥锁的状态发生改变时唤醒线程。  
