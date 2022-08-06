#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class MyPrint1
{
public:
    void operator()(int num)
    {
        cout << num << endl;
    }
};

void testMyPrint1()
{
    MyPrint1 mp;
    mp(10); // output: 10
}

class MyPrint2
{
public:
    void operator()(int num)
    {
        cout << num << endl;
        m_count++;
    }
    int m_count = 0;
};

void testMyPrint2()
{
    MyPrint2 mp;
    mp(10);
    mp(10);
    mp(10);
    mp(10);

    cout << mp.m_count << endl; // 4
}

void run(MyPrint1 mp, int num)
{
    mp(num);
}

void test3()
{
    run(MyPrint1(), 10); //传递匿名对象
}

class greaterThan20
{
public:
    bool operator()(int val)
    {
        return val > 20;
    }
};

void test4()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    vector<int>::iterator pos = find_if(v.begin(), v.end(), greaterThan20());
    if (pos != v.end())
        cout << *pos << endl; // 30
    else
        cout << "not found" << endl;
}

class MyCmp
{
public:
    bool operator()(int v1, int v2)
    {
        return v1 > v2;
    }
};

void printVector(vector<int>& v)
{
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void test5()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(20);
    v.push_back(40);

    sort(v.begin(), v.end(), MyCmp());
    //[](){} 匿名函数 lambda
    for_each(v.begin(), v.end(), [](int val){cout << val << " ";}); // 40 30 20 10
    cout << endl;
}

void test6()
{
    negate<int> n;
    cout << n(10) << endl; // -10

    plus<int> p;
    cout << p(1, 1) << endl;  // 2

    divides<int> d1;
    cout << d1(6, 3) << endl; // 2

    divides<double> d2;
    cout << d2(1, 3) << endl; //0.333333

}

void test7()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(20);
    v.push_back(40);

    sort(v.begin(), v.end(), greater<int>());
    for_each(v.begin(), v.end(), [](int val){cout << val << " ";}); // 40 30 20 10
    cout << endl;

    sort(v.begin(), v.end(), less<int>());
    for_each(v.begin(), v.end(), [](int val){cout << val << " ";}); // 10 20 30 40
    cout << endl;
}

int main()
{

    //testMyPrint2();
    //test3();
    //test4();
    //test5();
    //test6();
    test7();
    return 0;
}
