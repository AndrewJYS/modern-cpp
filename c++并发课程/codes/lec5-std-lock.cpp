#include <iostream>
#include <mutex>
#include <thread>
#include <list>
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

            std::lock(my_mutex1, my_mutex2);
            msgRecvQueue.push_back(i);
            my_mutex2.unlock(); //解锁
            my_mutex1.unlock();
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

int main()
{
    test1();

    return 0;
}
