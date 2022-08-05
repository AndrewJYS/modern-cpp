#include <iostream>
#include <thread>
using namespace std;

class A
{
public:
    int m_i;

    A(int a): m_i(a)
    {
        cout << "含参构造函数: " << this << "; thread_id = " << std::this_thread::get_id() << endl;
    }

    A(const A& a)
    {
        m_i = a.m_i;
        cout << "拷贝构造函数: " << this << "; thread_id = " << std::this_thread::get_id() << endl;
    }

    ~A()
    {
        cout << "析构函数: " << this << "; thread_id = " << std::this_thread::get_id() << endl;
    }

};

void my_print(const A& a)
{
    cout << "子线程的参数地址是" << &a << "; thread_id = " << std::this_thread::get_id() << endl;
}

void test_id1()
{
    cout << "主线程id: " << std::this_thread::get_id() << endl;
    int state = 0;
    thread my_thread(my_print, state);
    my_thread.join();
    /*
    主线程id: 1
    含参构造函数: 0xf4fda0; thread_id = 2
    子线程的参数地址是0xf4fda0; thread_id = 2
    析构函数: 0xf4fda0; thread_id = 2
    */
}

void test_id2()
{
    cout << "主线程id: " << std::this_thread::get_id() << endl;
    int state = 0;
    thread my_thread(my_print, A(state));
    my_thread.join();
    /*
    主线程id: 1
    含参构造函数: 0x73fdd0; thread_id = 1
    拷贝构造函数: 0x73fd70; thread_id = 1
    拷贝构造函数: 0x1b2588; thread_id = 1
    析构函数: 0x73fd70; thread_id = 1
    析构函数: 0x73fdd0; thread_id = 1
    子线程的参数地址是0x1b2588; thread_id = 2
    析构函数: 0x1b2588; thread_id = 2
    */
}

int main()
{
    //test_id1();
    test_id2();

    return 0;
}
