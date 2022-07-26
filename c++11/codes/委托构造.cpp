#include <iostream>
using namespace std;

class Test
{
public:
    // 委托构造一定要通过初始化列表方式
    Test(): Test(1, 'a') {}
    Test(int x): Test(x, 'b') {}
    Test(char x): Test(11, x) {}

    int a;
    char b;

private:
    Test(int x, char y): a(x), b(y) {}
};

int main()
{
    Test t1;
    cout << t1.a << endl; // 1
    cout << t1.b << endl; // a

    Test t2(10);
    cout << t2.a << endl; // 10
    cout << t2.b << endl; // b

    Test t3('c');
    cout << t3.a << endl; // 11
    cout << t3.b << endl; // c

    return 0;
}
