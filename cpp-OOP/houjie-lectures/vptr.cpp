#include <iostream>
using namespace std;

class A
{
public:
    int m_data1, m_data2;
    virtual void vfunc1() {}
    virtual void vfunc2() {}
    void func1();
    void func2();
};

class B: public A
{
public:
    int m_data1, m_data3;
    virtual void vfunc1(){};
    void func2();
};

int main()
{
    A a;
    cout << sizeof(a) << endl;

    B b;
    cout << sizeof(b) << endl;

    return 0;
}
