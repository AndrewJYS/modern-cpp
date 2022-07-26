#include <iostream>
using namespace std;

class B
{
public:
    B(int i): m_i(i) {}

    int m_i;
};

class A
{
public:
    int data1 = 1;
    int data2{2};
    B data3{3};
    string data4{"4"};
};

int main()
{
    A a;
    cout << a.data1 << endl;    // 1
    cout << a.data2 << endl;    // 2
    cout << a.data3.m_i << endl;// 3
    cout << a.data4 << endl;    // 4

    return 0;
}
