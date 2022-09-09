#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
using namespace std::placeholders;

void myPrint(int val)
{
    cout << val << " ";
}

class MyPrint
{
public:
    void operator()(int val)
    {
        cout << val << " ";
        m_count++;
    }
    int m_count = 0;
};

class MyPrint2
{
public:
    void operator()(int val, int start) const
    {
        cout << val + start << " ";
    }
};

void test1()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    // for_each()接受函数回调或函数对象
    for_each(v.begin(), v.end(), myPrint); // 0 1 2 3 4 5 6 7 8 9
    cout << endl;

    for_each(v.begin(), v.end(), MyPrint()); // 0 1 2 3 4 5 6 7 8 9
    cout << endl;

    // for_each 有返回值
    MyPrint mp = for_each(v.begin(), v.end(), MyPrint()); // 0 1 2 3 4 5 6 7 8 9
    cout << endl;
    cout << "m_count is " << mp.m_count << endl; // m_count is 10

    // for_each可以绑定参数输出（使用适配器）
    for_each(v.begin(), v.end(), bind(MyPrint2(), _1, 1000)); // 1000 1001 1002 1003 1004 1005 1006 1007 1008 1009
    cout << endl;
}

int main()
{
    test1();

    return 0;
}
