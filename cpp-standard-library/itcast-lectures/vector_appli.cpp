#include <iostream>
#include <vector>
using namespace std;

void test1()
{
    // 利用swap收缩空间
    vector<int> v;
    for (int i = 0; i < 100000; i++)
    {
        v.push_back(i);
    }
    cout << "capacity: " << v.capacity() << "; size: " << v.size() << endl;

    v.resize(3);
    cout << "capacity: " << v.capacity() << "; size: " << v.size() << endl;

    vector<int>(v).swap(v);
    cout << "capacity: " << v.capacity() << "; size: " << v.size() << endl;
}

void test2()
{
    // 逆序遍历
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(50);
    v.push_back(40);

    for (vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); it++)
    {
        cout << *it << " " << endl;
    }
    cout << endl;
}

void test3()
{
    // 测试迭代器是否支持随机访问
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(50);
    v.push_back(40);

    vector<int>::iterator it = v.begin();
    it++;
    it--; // ++, -- 都通过，则是双向迭代器
    it = it + 1; // 如果通过，则该迭代器支持随机访问
}

void test4()
{
    vector<int> v;
    v.reserve(1000);
    cout << v.size() << " " << v.capacity() << endl;
}

int main()
{
    //test1();
    //test2();
    //test3();
    test4();
    return 0;
}
