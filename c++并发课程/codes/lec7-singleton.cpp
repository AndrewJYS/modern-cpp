#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

std::mutex my_mutex;

class Singleton
{
public:
    static Singleton* getInstance()
    {
        if (nullptr == m_instance) //双重检查
        {
            std::unique_lock<std::mutex> uq(my_mutex);

            if (nullptr == m_instance)
            {
                m_instance = new Singleton();
                static Delete_ dl;
                // cout << "create\n"; //这行可以证明只执行了一次
            }
        }
        return m_instance;
    }

    class Delete_ //这个类用来析构单例
    {
    public:
        ~Delete_()
        {
            if (Singleton::m_instance)
            {
                delete Singleton::m_instance;
                Singleton::m_instance = nullptr;
            }
        };
    };

    void func()
    {
        cout << "test\n";
    }

private:
    Singleton(){}
    static Singleton* m_instance;
};

Singleton* Singleton::m_instance = nullptr;

void test()
{
    Singleton* ps1 = Singleton::getInstance();
    Singleton* ps2 = Singleton::getInstance();

    if (ps1 == ps2)
    {
        cout << "ps1 and ps2 are the same instance" << endl;
    }

    ps2->func();
}


void thread_work()
{
    cout << "thread_work begins\n";
    Singleton* ps = Singleton::getInstance();
    ps->func();
    cout << "thread_work ends\n";
}

void test2()
{
    std::thread my_thread1(thread_work);
    std::thread my_thread2(thread_work);
    my_thread1.join();
    my_thread2.join();

    return ;
}

int main()
{
//    test();
    test2();

    return 0;
}
