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

void my_print(A& a)
{
    a.m_i = 199;
    cout << "子线程的参数地址是" << &a << "; thread_id = " << std::this_thread::get_id() << endl;
}

void test()
{
    cout << "主线程id: " << std::this_thread::get_id() << endl;
    A a(10);
    thread my_thread(my_print, std::ref(a));
    my_thread.join();
    cout << "a.m_i: " << a.m_i << endl;

    /*
    主线程id: 1
    含参构造函数: 0x73fdc0; thread_id = 1
    子线程的参数地址是0x73fdc0; thread_id = 2
    a.m_i: 199
    析构函数: 0x73fdc0; thread_id = 1
    */
}

int main()
{
    test();

    return 0;
}
