#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    // assert 在运行时检查条件，如果条件为真，则继续执行，否则终止
    bool cond = false;
    assert(cond); // Assertion failed!

    // 静态断言可以在编译时就判断条件，减小开销
    // static_assert(常量表达式条件, "提示的字符串");
    static_assert(sizeof(void*) == 4, "32位");

    return 0;

}
