#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;

// 普通函数
void func1()
{
    cout << __func__ << endl;
}

// 类中静态函数
class Test
{
public:
    static int test_func(int tmp)
    {
        cout << __func__ << "(" << tmp << ") -> ";
        return tmp;
    }
};

// 仿函数
class MyFunctor
{
public:
    int operator()(int tmp)
    {
        cout << __func__ << "(" << tmp << ") -> ";
        return tmp;
    }
};

void test_function()
{
    // 绑定普通函数
    function<void(void)> f1 = func1; // <void(void)> 括号内的void是指函数的参数类型，第一个void是函数返回值
    f1(); // func1

    // 绑定类中的静态函数
    function<int(int)> f2 = Test::test_func;
    cout << f2(10) << endl; // test_func(10) -> 10

    // 绑定仿函数
    MyFunctor obj;
    function<int(int)> f3 = obj;
    cout << f3(8) << endl; // operator()(8) -> 8
}



void func(int x, int y)
{
    cout << x << " " << y << endl;
}

void test_bind()
{
     bind(func, 11, 22)(); // 11 22

     // std::placeholders::_1，函数调用时，被bind末尾()中第一个参数替换
     // std::placeholders::_2，函数调用时，被第二个参数替换
     bind(func, _1, _2)(11, 22); // 11 22
     bind(func, 11, _1)(2, 3, 4); // 11 2
     bind(func, _3, 11)(1, 3, 5); // 5 11
     bind(func, _2, _1)(11, 22); // 22 11
}


int main()
{
    test_function();
    test_bind();

    return 0;
}
