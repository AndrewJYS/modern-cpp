#include <iostream>
#include <thread>
using namespace std;


class Func1
{
public:
    void operator()()
    {
        cout << "Func1 begins" << endl;
        cout << "Func1 ends" << endl;
    }
};

void test_Func1()
{
    Func1 func;
    thread my_thread(func);
    my_thread.join();

    cout << "hello world" << endl;
}


class Func2
{
public:
    int& m_i;
    Func2(int& i): m_i(i) {}

    void operator()()
    {
        for (int j = 0; j < 100; ++j)
        {
            cout << j << ": " << m_i << endl;
        }
    }
};

void test_Func2()
{
    int state = 10;
    Func2 func(state);
    thread my_thread(func);
    //my_thread.join();
    my_thread.detach(); //危险！state被主线程回收后，子线程会发生不可预料的结果

    cout << "hello world" << endl;
}


class Func3
{
public:
    Func3()
    {
        cout << "无参构造函数" << endl;
    }

    Func3(const Func3& f)
    {
        cout << "拷贝构造函数" << endl;
    }

    ~Func3()
    {
        cout << "析构函数" << endl;
    }

    void operator()()
    {
        cout << "Func3 begins" << endl;
        cout << "Func3 ends" << endl;
    }
};

void test_Func3()
{
    Func3 func;
    thread my_thread(func);
    my_thread.join();
    //my_thread.detach();

    cout << "hello world" << endl;
}


void my_func()
{
    cout << "my function begins" << endl;

    cout << "do 1" << endl;
    cout << "do 2" << endl;
    cout << "do 3" << endl;
    cout << "do 4" << endl;
    cout << "do 5" << endl;

    cout << "my function ends" << endl;
}

void test_my_func()
{
    thread my_thread(my_func); //创建线程，线程的执行起点为my_func，my_thread线程开始执行

    //join():阻塞主线程并等待子线程执行完
    my_thread.join(); //阻塞主线程并等待子线程执行完

    //detach():子线程相当于被运行时库接管，当这个子线程执行完之后，由运行时库负责清理该线程的相关资源
    // 一旦调用了detach()，就不能再调用join()
    //my_thread.detach();

    //joinable():判断是否可以调用join()或detach()
    //true表示可以，false表示不行
    if (my_thread.joinable())
    {
        cout << "joinable" << endl;
    }
    else
    {
        cout << "not joinable" << endl;
    }

    cout << "hello world" << endl;
    cout << "end 1" << endl;
    cout << "end 2" << endl;
    cout << "end 3" << endl;
}


void test_lambda()
{
    auto p = []{
        cout << "my lambda begins" << endl;
        cout << "my lambda ends" << endl;
    };

    thread my_thread(p);
    my_thread.join();

    cout << "hello world" << endl;
}

int main()
{
    //test_my_func();
    //test_Func1();
    //test_Func2();
    //test_Func3();
    test_lambda();

    return 0;
}
