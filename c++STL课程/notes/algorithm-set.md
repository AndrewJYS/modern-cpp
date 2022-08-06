# 集合相关算法  

## 交集  

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; 

void test1()
{
    // 集合的交集,set_intersection()
    // set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), targetV.begin());
    // 返回targetV[交集.size()]迭代器，具体见示例
    vector<int> v1;
    vector<int> v2;

    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 5);
    }


    vector<int> targetV;
    targetV.resize(min(v1.size(), v2.size()));
    vector<int>::iterator pos = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), targetV.begin());
    cout << *pos << endl; // 0

    for_each(targetV.begin(), pos, [](int val){cout << val << " ";}); // 5 6 7 8 9
    cout << endl;
}
```

## 并集  

```c++
void test2()
{
    // 集合的并集,set_union()
    // set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), targetV.begin());
    vector<int> v1;
    vector<int> v2;

    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 5);
    }


    vector<int> targetV;
    targetV.resize(v1.size() + v2.size());
    vector<int>::iterator pos = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), targetV.begin());

    for_each(targetV.begin(), pos, [](int val){cout << val << " ";});
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
    cout << endl;
}
```

## 差集  

```c++
void test3()
{
    // 集合的并差集,set_difference()
    // set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), targetV.begin());
    vector<int> v1;
    vector<int> v2;

    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 5);
    }


    vector<int> targetV;
    targetV.resize(max(v1.size(), v2.size()));
    vector<int>::iterator pos = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), targetV.begin());

    for_each(targetV.begin(), pos, [](int val){cout << val << " ";}); // 0 1 2 3 4
    cout << endl;
}
```
