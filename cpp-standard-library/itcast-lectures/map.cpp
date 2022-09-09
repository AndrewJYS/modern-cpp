#include <iostream>
#include <map>
using namespace std;

void printMap(map<int, int>& m)
{
    for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout << "(" << (*it).first << ", " << (*it).second << ")";
    }
    cout << endl;
}

void test1()
{
    map<int, int> m;

    // 插入
    m.insert(pair<int, int>(1, 10));
    m.insert(make_pair(2, 20));
    m.insert(map<int, int>::value_type(3, 30));
    m[4] = 40;
    printMap(m); // (1, 10)(2, 20)(3, 30)(4, 40)

    // 按照key值删除元素
    m.erase(3);
    printMap(m); // (1, 10)(2, 20)(4, 40)

    // 查找
    map<int, int>::iterator pos = m.find(3);
    if (pos != m.end())
        cout << "(" << (*pos).first << ", " << (*pos).second << ")";
    else
        cout << "not found" << endl; // 输出not found

    // 统计, count()返回0或1
    int num = m.count(4);
    cout << num << endl; // 1

    // lower_bound(keyElem), 返回第一个key >= keyElem的元素的迭代器，找不到则返回end()
    map<int, int>::iterator low = m.lower_bound(2);
    // 下述例子输出 lower bound is 2
    if (low != m.end())
        cout << "lower bound is " << (*low).first << endl;
    else
        cout << "lower bound not found" << endl;


    // upper_bound(keyElem), 返回第一个key > keyElem的元素的迭代器，找不到则返回end()
    map<int, int>::iterator upp = m.upper_bound(2);
    // 下述例子输出 upper bound is 4
    if (upp != m.end())
        cout << "upper bound is " << (*upp).first << endl;
    else
        cout << "upper bound not found" << endl;


    // equal_range(keyElem) 返回pair<lower_bound(keyElem), upper_bound(keyElem)>
    pair<map<int, int>::iterator, map<int, int>::iterator> it = m.equal_range(2);
    if (it.first != m.end())
        cout << "lower bound is " << (*(it.first)).first << endl;
    else
        cout << "lower bound not found" << endl;
    if (it.second != m.end())
        cout << "upper bound is " << (*(it.second)).first << endl;
    else
        cout << "upper bound not found" << endl;
}

class MyCMP
{
public:
    bool operator()(int v1, int v2)
    {
        return v1 > v2;
    }
};

void test2()
{
    map<int, int, MyCMP> m;
    m.insert(pair<int, int>(1, 10));
    m.insert(make_pair(2, 20));
    m.insert(map<int, int>::value_type(3, 30));
    m[4] = 40;

    for (map<int, int, MyCMP>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout << "(" << (*it).first << ", " << (*it).second << ")";
    }
    cout << endl; // (4, 40)(3, 30)(2, 20)(1, 10)
}

int main()
{
    test1();
    test2();

    return 0;
}
