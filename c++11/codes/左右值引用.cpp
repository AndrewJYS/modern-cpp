#include <iostream>
using namespace std;

int& func1()
{
    static int tmp = 0;
    return tmp;
}

void testL()
{
    // 引用：给一个内存起一个别名，定义时必须初始化
    // 左值引用 (&)
    int a;
    int& b = a; // 给a起一个别名
    //int& c = 1; // error
    const int& d = a;
    const int& e = 1; // OK
    const int& f = func1();
}

int func2()
{
    return 10;
}

void testR()
{
    // 右值引用 (&&)
    int && a = 10;
    int && b = func2();
    int i = 10;
    int j = 10;
    int && c = i + j;

    int k = 10;
    //int && d = k; //error.不能把一个左值赋值给一个右值引用
}

void test(int& tmp)
{
    cout << "left value is " << tmp << endl;
}

void test(int && tmp)
{
    cout << "right value is " << tmp << endl;
}

int main()
{
    testL();
    testR();

    int a = 10;
    test(a); // left value is 10
    test(111); // right value is 111

    return 0;
}
