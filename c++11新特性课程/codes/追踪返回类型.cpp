#include <iostream>
#include <typeinfo>
#include <vector>
using namespace std;

// auto返回值与->(?)一起使用，表明该函数返回值可以根据->后面的要求自动推导

auto func1(int a, double b) -> int
{
    return a + b;
}

auto func2(int a, double b) -> double
{
    return a + b;
}

auto func3(int a, double b) -> decltype(a + b)
{
    return a + b;
}

// 在结合模板使用的时候，会有更大的作用

template<class T1, class T2>
auto mul(T1& t1, T2& t2) -> decltype(t1 * t2)
{
    return t1 * t2;
}

int main()
{
    auto a = 10;
    auto b = 11.1;
    cout << func1(a, b) << endl; // 21
    cout << func2(a, b) << endl; // 21.1
    cout << func3(a, b) << endl; // 21.1

    auto c = 10;
    auto d = 11.11;
    cout << mul(c, d) << endl; // 111.1

    return 0;
}
