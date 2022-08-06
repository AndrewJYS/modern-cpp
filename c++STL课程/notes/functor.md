# 函数对象（仿函数）  

## 概述  

1.函数对象（仿函数）是一个类，不是一个函数。函数对象重载了（）操作符使得它可以像函数一样调用  

```c++
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
    MyPrint mp;
    mp(10); // output: 10
}
```

2.仿函数可以维护自己的状态  

```c++
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
```

3.仿函数可以作为参数进行传递  

```c++
void run(MyPrint1 mp, int num)
{
    mp(num);
}

void test3()
{
    run(MyPrint1(), 10); //传递匿名对象
}
```

其他注意点：  
函数对象通常不定义构造函数和析构函数  
函数对象可内联编译，性能好（用函数指针几乎不可能）  
模板函数对象使函数对具有通用性  

## 谓词  

谓词是指普通函数或重载的operator()返回值是bool类型的函数对象（仿函数）。如果operator接受一个参数，称作一元谓词，如果接受两个参数，称为二元谓词。谓词可作为一个判断式。  

下面这个例子表明，仿函数可以协助算法完成不同的策略  

```c++
// 一元谓词的例子
#include <iostream>
#include <algorithm>
using namespace std;

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

    // find_if()寻找v中第一个大于20的元素
    vector<int>::iterator pos = find_if(v.begin(), v.end(), greaterThan20());
    if (pos != v.end())
        cout << *pos << endl; // 30  
    else
        cout << "not found" << endl;
}
```

```c++
//二元谓词的例子 
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
```

## 内建函数对象  

STL内建了一些函数对象，分为算术类函数对象，关系运算类函数对象，逻辑运算类函数对象。这些函数对象所产生的对象，用法和一般函数完全相同。使用内建函数对象，要引入头文件functional.  

```c++
negate<int> n;
cout << n(10) << endl; // -10

plus<int> p;
cout << p(1, 1) << endl;  // 2

divides<int> d1;
cout << d1(6, 3) << endl; // 2

divides<double> d2;
cout << d2(1, 3) << endl; //0.333333
```

```c++
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
```
