#include <iostream>
using namespace std;

// 常量表达式允许一些计算发生在编译阶段，它将只做一次，而不是每次程序运行时都计算
// constexpr的限制：
// 函数中只能有一个语句，且为return语句，函数必须有返回值
// 但是函数中允许包含typedef, using, 静态断言
// return 语句中不能使用非常量表达式的函数，全局数据，只能是一个常量表达式

constexpr int getConst1()
{
    return 4 + 104;
}

constexpr int getConst2()
{
    //constexpr int a = 1; // 报错
    return 6;
}

constexpr int getConst3()
{
    typedef int INT;
    return 4;
}

const int aa = 6;
constexpr int getConst4()
{
    // return a;  // 报错
}

int getINT()
{
    return 4;
}
constexpr int getConst5()
{
    //return getINT(); // 报错
}

int main()
{
    int a = getConst1();
    cout << a << endl;

    return 0;
}
