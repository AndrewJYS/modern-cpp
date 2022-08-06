# 搜索  

find()  
find_if()  
adjacent_find()  
binary_search()  
count()  
count_if()  

## 常规查找  

```c++
void test1()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    //查找有没有5这个元素
    // find()返回第一个满足条件的元素的迭代器
    vector<int>::iterator pos = find(v.begin(), v.end(), 5);
    if (pos != v.end())
        cout << "find the element: " << *pos << endl;
    else
        cout << "not found" << endl;
}
```

## 自定义数据类型查找  

```c++
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

class MyCmp: public binary_function<Person, Person, bool>
{
public:
    bool operator()(Person p1, Person p2) const
    {
        return p1.m_name == p2.m_name && p1.m_age == p2.m_age;
    }
};

void test2()
{
    vector<Person> v;
    Person p1("a", 10);
    Person p2("b", 20);
    Person p3("c", 30);
    Person p4("d", 40);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    // 自定义数据类型使用find函数需要重载==运算符
    vector<Person>::iterator pos = find(v.begin(), v.end(), Person("a", 10));
    if (pos != v.end())
        cout << (*pos).m_name << " " << (*pos).m_age << endl; // a 10
    else
        cout << "not found" << endl;

    // 也可以不重载==运算符，使用find_if，但需要构造仿函数和适配器
    // // find_if()返回第一个满足条件的元素的迭代器
    vector<Person>::iterator pos2 = find_if(v.begin(), v.end(), bind2nd(MyCmp(), Person("a", 10)));
    if (pos2 != v.end())
        cout << (*pos2).m_name << " " << (*pos2).m_age << endl; // a 10
    else
        cout << "not found" << endl;
}
```

## 查找相邻元素  

```c++
void test3()
{
    // 查找相邻重复元素
    // 使用adjacent_find()，它返回第一个满足条件的元素的迭代器
    vector<int> v;
    v.push_back(1);
    v.push_back(4);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(6);
    v.push_back(6);
    v.push_back(17);

    vector<int>::iterator pos = adjacent_find(v.begin(), v.end());
    if (pos != v.end())
        cout << *pos << endl; // 6
    else
        cout << "not found" << endl;

}
```

## 二分查找  

```c++
void test4()
{
    // 二分查找排序数组中的元素
    // 使用binary_search()
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(5);
    v.push_back(8);
    v.push_back(13);

    bool res = binary_search(v.begin(), v.end(), 5);
    cout << res << endl; // 1
}
```

## 统计元素  

```c++
class MyCmp5
{
public:
    bool operator()(int val)
    {
        return val > 4;
    }
};

void test5()
{
    // 统计元素个数
    vector<int> v;
    v.push_back(4);
    v.push_back(4);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);

    cout << count(v.begin(), v.end(), 4) << endl; // 3

    // 按条件统计
    cout << count_if(v.begin(), v.end(), MyCmp5()) << endl; // 2
}
```
