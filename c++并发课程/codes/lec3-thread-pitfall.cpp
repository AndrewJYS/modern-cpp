#include <iostream>
#include <thread>
using namespace std;


void my_print1(const int& i, char* buf)
{
    cout << i << endl;
    //分析认为，i并不是var的引用，实际上是值传递；那么即使用了detach，也不会因为主线程提前终止，而找不到i的值

    cout << buf << endl;
    //指针在detach()使用过程中，会有问题
}

void test_my_print1()
{
    int var = 1;
    char buffer[] = "test";
    thread my_thread(my_print1, var, buffer);
    my_thread.detach();
    cout << "hello world" << endl;
}



void my_print2(const int& i, const string& buf)
{
    cout << i << endl;

    cout << buf << endl;
    //理论上，string会以值传递的形式，交给子线程
    //但是，这里存在一个类型转换的问题，传入的实参是char buffer[], 要转成string
    //如果detach()的情况下，主线程已经结束，而仍然没有将char数组转成string，就会有问题
}

void test_my_print2()
{
    int var = 1;
    char buffer[] = "test";
    thread my_thread(my_print2, var, buffer);
    my_thread.detach();
    cout << "hello world" << endl;
}

void test_my_print3()
{
    int var = 1;
    char buffer[] = "test";

    //针对上面的问题，改成string(buffer)后，即使使用detach()，程序也是安全的
    //在创建线程的同时构造临时对象传递是可行的
    //主线程运行到这一步时，会构造临时对象，然后主线程和子线程分开执行
    //也就是说，在主线程执行完毕之前，这个临时对象一定会被构造出来
    //即使主线程回收了，也不影响子线程继续使用这个对象
    thread my_thread(my_print2, var, string(buffer));
    my_thread.detach();
    cout << "hello world" << endl;
}

int main()
{
    test_my_print3();

    return 0;
}
