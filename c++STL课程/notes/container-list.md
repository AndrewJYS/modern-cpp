# list  

list容器是一个双向循环链表  

## 遍历  

遍历分别正序遍历和逆序遍历，和vector一样  

```c++
void printList(list<int>& L)
{
    for (list<int>::iterator it = L.begin(); it != L.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void printListReverse(list<int>& L)
{
    for (list<int>::reverse_iterator it = L.rbegin(); it != L.rend(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void testPrint()
{
    list<int> L;
    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    printList(L); // 1 2 3
    printListReverse(L);  //3 2 1
}
```

## 基本操作  

```c++
list<int> L;
L.push_back(1); // 尾部插入
L.push_back(2);
L.push_front(3); // 头部插入
printList(L); // 3 1 2
L.pop_back(); //尾部删除
L.pop_front(); // 头部删除
printList(L); // 1

cout << L.front() << endl; // 1
cout << L.back() << endl; // 1
cout << L.size() << endl; // 1
L.clear();
cout << L.empty() << endl; // 1
```

```c++
// 构造
list<int> L;
list<int> L2(6, 5);
printList(L2);  // 5 5 5 5 5 5
list<int> L3(L2.begin(), L2.end());
printList(L3);  // 5 5 5 5 5 5

// 插入
L3.insert(L3.begin(), 1000);
printList(L3); // 1000 5 5 5 5 5 5

// 删除所有匹配元素
L3.remove(5); // 删除所有与5匹配的元素
printList(L3); // 1000

// 赋值
list<int> L4;
L4.assign(4, 10);
printList(L4); // 10 10 10 10
L4.assign(L3.begin(), L3.end());
printList(L4); // 1000

// 逆序
L.push_back(10);
L.push_back(6);
L.push_back(9);
L.push_back(8);
printList(L); //  10 6 9 8
L.reverse();
printList(L); // 8 9 6 10
```

## 排序  

```c++
list<int> L;
L.push_back(10);
L.push_back(6);
L.push_back(9);
L.push_back(8);
// sort(L.begin(), L.end())会报错，原因是list不支持随机访问的迭代器
// 不支持随机访问的迭代器的容器，内部会提供相应的算法接口

// 从小到大排序
L.sort();
printList(L); // 6 8 9 10

// 从大到小排序
L.sort(cmp);
printList(L); // 10 9 8 6
```

“从大到小”比较器如下：

```c++
const bool cmp(int v1, int v2)
{
    return v1 > v2;
}
```

## 自定义数据类型的排序  

```c++
class Person
{
public:
    Person(string name, int age, int height)
    {
        this->m_name = name;
        this->m_age = age;
        this->m_height = height;
    }
public:
    string m_name;
    int m_age;
    int m_height;
};

void printPerson(const list<Person>& L)
{
    for (list<Person>::const_iterator it = L.begin(); it != L.end(); it++)
    {
        cout << "name: " << (*it).m_name << "; age: " << (*it).m_age << "; height: " << (*it).m_height << endl;
    }
}

const bool personCMP(Person p1, Person p2)
{
    // 按照年龄升序排列
    // 当年龄相同时按照身高降序排列
    if (p1.m_age == p2.m_age)
        return p1.m_height > p2.m_height;
    return p1.m_age < p2.m_age;
}

void test3()
{
    Person p1("mike", 10, 170);
    Person p2("anne", 5, 170);
    Person p3("emma", 7, 174);
    Person p4("jack", 15, 176);
    Person p5("john", 15, 175);
    Person p6("jane", 15, 179);

    list<Person> L;
    L.push_back(p1);
    L.push_back(p2);
    L.push_back(p3);
    L.push_back(p4);
    L.push_back(p5);
    L.push_back(p6);

    L.sort(personCMP);
    printPerson(L);

    /* 输出
    name: anne; age: 5; height: 170
    name: emma; age: 7; height: 174
    name: mike; age: 10; height: 170
    name: jane; age: 15; height: 179
    name: jack; age: 15; height: 176
    name: john; age: 15; height: 175
    */
}
```

## 自定义数据类型中的remove操作  

如果list加入自定义数据类型的元素后使用remove会报错，原因是remove函数隐含了相等的判断，而自定义数据类型不能直接做==判断，因此要重载==运算符  

```c++
class Person
{
public:
    ......

    bool operator==(const Person& p)
    {
        if (this->m_name == p.m_name && this->m_age == p.m_age && this->m_height == p.m_height)
            return true;
        return false;
    }

    ......
};

void printPerson(const list<Person>& L)
{
    //同上
}

const bool personCMP(Person p1, Person p2)
{
    //同上
}

void test3()
{
    //同上

    L.remove(p5);
    printPerson(L);
    /* 输出
    name: anne; age: 5; height: 170
    name: emma; age: 7; height: 174
    name: mike; age: 10; height: 170
    name: jane; age: 15; height: 179
    name: jack; age: 15; height: 176
    */
}
```
