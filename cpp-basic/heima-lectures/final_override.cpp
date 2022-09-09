#include <iostream>
using namespace std;

// final会阻止类的进一步派生，虚函数的进一步重写

class A1 final
{
    int a;
};

// class A2: public A1; //报错

class B1
{
public:
    virtual void run() final;
};

class B2: public B1
{
public:
    // void run() {} // 报错
};

class C1
{
public:
    // 这是第一个虚函数，没有重写，不能用override修饰
    virtual void run(int a) = 0;
};

class C2: public C1
{
public:
    // 在重写虚函数的地方，加上override，要求重写的虚函数和基类一模一样
    void run(int a) override {}
    //void run() override {} // 报错
    //int run() override {return 1;} // 报错
};

int main()
{

}
