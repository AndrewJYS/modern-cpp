#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void test00()
{
    vector<int> a;
    for (int i = 0; i < 10; i++)
        a.push_back(i); // 末尾插入
    a.pop_back(); //末尾删除
    cout << a.size() << endl;  // 9
    cout << a.capacity() << endl; // 16
    cout << a.front() << endl; // 0, 首元素
    cout << a.back() << endl; // 8, 尾元素
    a.clear(); //清空
    cout << a.empty() << endl; // 1
}

void test01()
{
    int arr[5] = {1, 4, 6, 7, 0};
    int* p  = arr;
    for (int i = 0; i < 5; i++)
    {
        cout << *(p++) << " ";
    }
    cout << endl;
}

void myPrint(int val)
{
    cout << val << " ";
}

void test02()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(50);
    v.push_back(40);

    // traversal 1
    vector<int>::iterator it = v.begin();
    while (it != v.end())
    {
        cout << (*it) << " " ;
        it++;
    }
    cout << endl;

    // traversal 2
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << (*it) << " " ;
    }
    cout << endl;

    // traversal 3, need algorithm header
    for_each(v.begin(), v.end(), myPrint);
    cout << endl;
}

class Person
{
public:
    Person(string name, int age)
    {
        this->m_name = name;
        this->m_age = age;
    }

public:
    string m_name;
    int m_age;
};

void test03()
{ //容器添加自定义类型对象
    vector<Person> v;

    Person p1("a", 1);
    Person p2("b", 1);
    Person p3("c", 1);
    Person p4("d", 1);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "name: " << (*it).m_name << "; age: " << (*it).m_age << endl;
    }
}

void test04()
{
    vector<Person*> v;

    Person* p1 = new Person("a", 1);
    Person* p2 = new Person("b", 1);
    Person* p3 = new Person("c", 1);
    Person* p4 = new Person("d", 1);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    for (vector<Person*>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "name: " << (*it)->m_name << "; age: " << (*it)->m_age << endl;
    }
}

void test05()
{
    vector<vector<int>> v; //嵌套容器

    vector<int> v1 = {1,2,3};
    vector<int> v2 = {2,4,5};
    vector<int> v3 = {5,7,9};
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);

    for (vector<vector<int>>::iterator it = v.begin(); it != v.end(); it++)
    {
        // (*it) ----- vector<int>
        for (vector<int>::iterator vit = (*it).begin(); vit != (*it).end(); vit++)
        {
            // (*vit) ----- int
            cout << *vit << " ";
        }
        cout << endl;
    }
}

void printVector(vector<int>& v)
{
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << (*it) << " ";
    }
    cout << endl;
}

void test06()
{
    // 构造
    vector<int> v1;
    vector<int> v2(10, 100); //把10个100拷贝给本身
    printVector(v2); // 100 100 100 100 100 100 100 100 100 100

    vector<int> v3(v2.begin(), v2.end()); // 将v2[begin(), end())区间内的元素拷贝给本身
    printVector(v3); // 100 100 100 100 100 100 100 100 100 100

    int arr[] = {1, 3, 5, 7, 8};
    vector<int> v4(arr, arr + sizeof(arr) / sizeof(int));
    printVector(v4); // 1 3 5 7 8

    // 赋值
    vector<int> v5;
    v5.assign(v2.begin(), v2.end()); // 将v2[begin(), end())区间内的元素赋值给本身
    printVector(v5);  // 100 100 100 100 100 100 100 100 100 100

    // 交换
    v4.swap(v5);
    printVector(v4); // 100 100 100 100 100 100 100 100 100 100
    printVector(v5); //1 3 5 7 8

    // 重新指定容器长度（重新指定size大小）
    v5.resize(10);
    printVector(v5); // 1 3 5 7 8 0 0 0 0 0
    v5.resize(3);
    printVector(v5); // 1 3 5

    // 插入
    v5.insert(v5.begin(), 0);
    printVector(v5);// 0 1 3 5
    v5.insert(v5.end(), 2, 0);
    printVector(v5);// 0 1 3 5 0 0

    // 删除
    v5.erase(v5.begin());
    printVector(v5); // 1 3 5 0 0
    v5.erase(v5.begin(), v5.end());
    printVector(v5); // 等同于v5.clear()
}

int main()
{
    test00();
    //test01();
    //test02();
    //test03();
    //test04();
    //test05();
    //test06();
    return 0;
}
