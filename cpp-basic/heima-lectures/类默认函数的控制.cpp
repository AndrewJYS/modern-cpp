#include <iostream>
using namespace std;

class A
{
public:
    // =default让编译器提供一个默认的构造函数，效率比用户写的高
    // =default只能修饰类中默认提供的构造函数：无参构造函数，拷贝构造函数，赋值运算符重载，析构函数等
    A() =default;
    A(int i): m_i(i){}

    int m_i;
};

class B
{
public:
    B() { cout << "无参构造函数" << endl; }
    B(const B&) { cout << "拷贝构造函数" << endl; }
    B& operator=(const B& ) {cout << "赋值运算符重载函数" << endl; return *this; }
};

class C
{
public:
    // =delete 可以禁用函数，也可以禁用一般函数
    C() { cout << "无参构造函数" << endl; }
    C(const C&)=delete; // 用=delete修饰，此函数被禁用
    C& operator=(const C& )=delete;

    void print(const C& c)=delete;

    // =delete还可以禁用运算符
    void* operator new(size_t)=delete;
    void* operator new[](size_t)=delete;
};

int main()
{
    A a;
    B obj1;
    B obj2(obj1);
    obj2 = obj1;

    C obj3;
    // C obj4(obj3); // 报错，拷贝构造函数被禁用

    //C* p = new C; // 报错，new运算符被禁用
    //C* parr = new C[10]; // 报错，new[]运算符被禁用
    //obj3.print(obj3);  //报错

    return 0;
}
