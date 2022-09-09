#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;
using namespace std::placeholders;

class Person
{
public:
    Person(string name, int age)
    {
        this->m_name = name;
        this->m_age = age;
    }

    bool operator==(Person p)
    {
        return this->m_name == p.m_name && this->m_age == p.m_age;
    }

    string m_name;
    int m_age;
};

class MyCmp
{
public:
    bool operator()(Person p1, Person p2) const
    {
        return p1.m_name == p2.m_name && p1.m_age == p2.m_age;
    }
};

void test()
{
    vector<Person> v {Person("a", 10), Person("b", 20), Person("c", 30), Person("d", 40)};

    // 自定义数据类型使用find函数需要重载==运算符
    vector<Person>::iterator pos = find(v.begin(), v.end(), Person("a", 10));
    if (pos != v.end())
        cout << (*pos).m_name << " " << (*pos).m_age << endl; // a 10
    else
        cout << "not found" << endl;

    // 也可以不重载==运算符，使用find_if，但需要构造仿函数和适配器
    // find_if()返回第一个满足条件的元素的迭代器
    vector<Person>::iterator pos2 = find_if(v.begin(), v.end(), bind(MyCmp(), _1, Person("a", 10)));
    if (pos2 != v.end())
        cout << (*pos2).m_name << " " << (*pos2).m_age << endl; // a 10
    else
        cout << "not found" << endl;
}

int main()
{
    test();

    return 0;
}
