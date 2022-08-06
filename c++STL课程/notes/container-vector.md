# vector  

## 基本操作  

```c++
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
printVector(v5);  // 1 3 5

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
```

上述所需的printVector()函数如下  

```c++
void printVector(vector<int>& v)
{
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << (*it) << " ";
    }
    cout << endl;
}
```

## 遍历一维vector  

有三种运用迭代器遍历vector的方式，for，while，for_each(需要引入algorithm头文件)

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> v;
v.push_back(10);
v.push_back(30);
v.push_back(50);
v.push_back(40);
```
  
```c++
// traversal 1
vector<int>::iterator it = v.begin();
while (it != v.end())
{
    cout << (*it) << " " ;
    it++;
}
cout << endl;
```
  
```c++
// traversal 2
for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
{
    cout << (*it) << " " ;
}
cout << endl;
```
  
```c++
// traversal 3, need algorithm header
for_each(v.begin(), v.end(), myPrint);
cout << endl;

void myPrint(int val)
{
    cout << val << " ";
}

```

## 遍历二维vector  

```c++
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
```

## 自定义类型作为Vector元素  

```c++
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

void test1()
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

void test2()
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
```

## vector函数的一些应用  

利用swap函数收缩内存  
利用reserve函数预留空间  
逆序遍历  
测试迭代器是否支持随机访问  

### 利用swap函数收缩内存  

```c++
vector<int> v;
for (int i = 0; i < 100000; i++)
{
    v.push_back(i);
}
cout << "capacity: " << v.capacity() << "; size: " << v.size() << endl;

v.resize(3);
cout << "capacity: " << v.capacity() << "; size: " << v.size() << endl;

//vector<int>(v)利用拷贝构造初始化匿名对象，swap()之后，系统会自动释放匿名对象的内存
vector<int>(v).swap(v);
cout << "capacity: " << v.capacity() << "; size: " << v.size() << endl;
```

```c++
//输出
capacity: 131072; size: 100000
capacity: 131072; size: 3
capacity: 3; size: 3
```

### 利用reserve函数预留空间  

如果首先用reserve()预留n个元素的空间(capacity)，那么随着不断插入元素，直到插满n个元素，此过程中系统不必为vector扩充空间(capacity)了。由于每次扩充空间有一个复制的操作，如果一开始就预留空间，就可以提高效率  

```c++
vector<int> v;
v.reserve(1000);
cout << v.size() << " " << v.capacity() << endl; // 0 1000
```

### 逆序遍历  

注意要用reverse_iterator  

```c++
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
```

### 测试迭代器是否支持随机访问  

```c++
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
```

## 注意size()和capacity()  

```c++
vector<int> v;
v.reserve(10);
cout << v.capacity() << endl; // 10
cout << v.size() << endl; // 0
cout << v[8] << endl; // 0
cout << v.capacity() << endl; // 10
cout << v.size() << endl; // 0
```
