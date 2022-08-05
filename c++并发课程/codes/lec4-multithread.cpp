#include <iostream>
#include <thread>
#include <vector>
#include <list>
using namespace std;

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



class A
{
public:
    // 收取消息
    void inMsgRecvQueue()
    {
        for (int i = 0; i < 100000; i++)
        {
            cout << "inMsgRecvQueue()执行，插入一个元素" << i << endl;
            msgRecvQueue.push_back(i);
        }
    }

    //抽取消息处理
    void outMsgRecvQueue()
    {
        for (int i = 0; i < 100000; ++i)
        {
            if (!msgRecvQueue.empty())
            {
                int command = msgRecvQueue.front();
                msgRecvQueue.pop_front();
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
};

void test2()
{
    A obj_a;
    std::thread out_thread(&A::outMsgRecvQueue, &obj_a);
    std::thread in_thread(&A::inMsgRecvQueue, &obj_a);
    out_thread.join();
    in_thread.join();

    return;
}

int main()
{
    //test1();
    test2();

    return 0;
}
