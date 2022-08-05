#include <iostream>
#include <thread>
#include <memory>
#include <functional>
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

    void thread_work(int num)
    {
        cout << "子线程执行: " << this << "; thread_id = " << std::this_thread::get_id() << endl;
    }
};


void my_print(unique_ptr<int> a)
{
    cout << "子线程的参数地址是" << &a << "; thread_id = " << std::this_thread::get_id() << endl;
}

void test_pointer()
{
    cout << "主线程id: " << std::this_thread::get_id() << endl;
    unique_ptr<int> a(new int(100));
    thread my_thread(my_print, std::move(a));
    //cout << *a << endl; // error! 因为前面已经有std::move()
    my_thread.join();

    /*
    主线程id: 1
    子线程的参数地址是0xf3fda0; thread_id = 2
    */
}

void test_class_member_function_pointer()
{
    A a(10);
    thread my_thread(&A::thread_work, a, 15); // 类的成员函数指针，类对象，成员函数的参数
    my_thread.join();

    /*
    含参构造函数: 0x73fdc0; thread_id = 1
    拷贝构造函数: 0x73fd54; thread_id = 1
    拷贝构造函数: 0xb6258c; thread_id = 1
    析构函数: 0x73fd54; thread_id = 1
    子线程执行: 0xb6258c; thread_id = 2
    析构函数: 0xb6258c; thread_id = 2
    析构函数: 0x73fdc0; thread_id = 1
    */
}

void test_class_member_function_pointer2()
{
    A a(10);
    thread my_thread(&A::thread_work, &a, 15); // 类的成员函数指针，类对象，成员函数的参数
    my_thread.join();

    /*
    含参构造函数: 0x73fdc0; thread_id = 1
    子线程执行: 0x73fdc0; thread_id = 2
    析构函数: 0x73fdc0; thread_id = 1
    */
}

int main()
{
    //test_pointer();

    //test_class_member_function_pointer();
    test_class_member_function_pointer2();

    return 0;
}
