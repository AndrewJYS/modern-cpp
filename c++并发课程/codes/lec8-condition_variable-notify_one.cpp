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

int main()
{
    test1();

    return 0;
}
