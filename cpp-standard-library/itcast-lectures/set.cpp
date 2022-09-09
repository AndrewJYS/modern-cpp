#include <iostream>
#include <set>
using namespace std;

void printSet(const set<int>& S)
{
    for (set<int>::const_iterator it = S.begin(); it != S.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

class MyCMP
{
public:
    bool operator()(int v1, int v2)
    {
        return v1 > v2;
    }
};

void test1()
{
    set<int> s;
    s.insert(1);
    s.insert(6);
    s.insert(5);
    s.insert(4);
    s.insert(8);
    printSet(s); // 1 4 5 6 8

    s.erase(6);
    printSet(s);  // 1 4 5 8

    // 插入之前指定从大到小排序
    set<int, MyCMP> newS;
    newS.insert(1);
    newS.insert(6);
    newS.insert(5);
    newS.insert(4);
    newS.insert(8);

    for (set<int, MyCMP>::iterator it = newS.begin(); it != newS.end(); it++)
    {
        cout << *it << " "; // 8 6 5 4 1
    }
    cout << endl;
}

void test2()
{
    set<int> s;
    s.insert(1);
    s.insert(6);
    s.insert(5);
    s.insert(8);

    // 插入
    pair<set<int>::iterator, bool> ins = s.insert(8);
    if (ins.second)
        cout << "insert successfully" << endl;
    else
        cout << "fail to insert" << endl; // 输出fail to insert

    // 查找，如果找到则返回该元素的迭代器，否则返回end()
    set<int>::iterator pos = s.find(3);
    // 下述例子输出 not found
    if (pos != s.end())
        cout << "find the element" << endl;
    else
        cout << "not found" << endl;


    // 计数，count()返回0或1
    cout << s.count(8) << endl; // 1
    cout << s.count(3) << endl; // 0


    // lower_bound(keyElem), 返回第一个 >= keyElem的元素的迭代器，找不到则返回end()
    set<int>::iterator low = s.lower_bound(0);
    // 下述例子输出 lower bound is 1
    if (low != s.end())
        cout << "lower bound is " << *low << endl;
    else
        cout << "lower bound not found" << endl;


    // upper_bound(keyElem), 返回第一个 > keyElem的元素的迭代器，找不到则返回end()
    set<int>::iterator upp = s.upper_bound(8);
    // 下述例子输出 lower bound not found
    if (upp != s.end())
        cout << "upper bound is " << *upp << endl;
    else
        cout << "upper bound not found" << endl;


    // equal_range(keyElem) 返回pair<lower_bound(keyElem), upper_bound(keyElem)>
    pair<set<int>::iterator, set<int>::iterator> it = s.equal_range(6);
    if (it.first != s.end())
        cout << "lower bound is " << *(it.first) << endl;
    else
        cout << "lower bound not found" << endl;
    if (it.second != s.end())
        cout << "upper bound is " << *(it.second) << endl;
    else
        cout << "upper bound not found" << endl;
    //lower bound is 6
    //upper bound is 8
}

int main()
{
    test1();
    test2();

    return 0;
}
