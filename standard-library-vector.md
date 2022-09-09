# vector  

A **vector** provides **random access**. Thus, you can access every element directly in constant time, provided that you know its position. The **iterators are random-access iterators**, so you can use any algorithm of the STL. Vectors provide **good performance** if you **append or delete elements at the end**. If you **insert or delete in the middle or at the beginning, performance gets worse**.

## vector的大小和容量  

### size()和capacity()  

```c++
vector<int> v;
v.reserve(10);
cout << v.capacity() << endl; // 10
cout << v.size() << endl; // 0
cout << v[8] << endl; // 0
cout << v.capacity() << endl; // 10
cout << v.size() << endl; // 0
```

**capacity()** function, which **returns the number of elements a vector could contain in its actual memory**. If you exceed the capacity(), the vector has to reallocate its internal memory.  

### 预留内存  

The capacity of a vector is important for two reasons:  
1.Reallocation invalidates all references, pointers, and iterators for elements of the vector.  
2.Reallocation takes time.  

**To avoid reallocation, you can use reserve()** to ensure a certain capacity before you really need it. In this way, you can ensure that references remain valid as long as the capacity is not exceeded:  

```cpp
std::vector<int> v; // create an empty vector
v.reserve(80); // reserve memory for 80 elements
cout << v.size() << " " << v.capacity() << endl; // 0 80

如果首先用reserve()预留n个元素的空间(capacity)，那么随着不断插入元素，直到插满n个元素，此过程中系统不必为vector扩充空间(capacity)了。由于每次扩充空间有一个复制的操作，如果一开始就预留空间，就可以提高效率  
```

### 收缩内存  

C++11 introduced a new member function for vectors: a nonbinding request to shrink the capacity to fit the current number of elements:  

```cpp
v.shrink_to_fit(); // request to shrink memory (since C++11)
```

**This request is nonbinding** to allow latitude for implementation-specific optimizations. Thus, **you cannot expect that afterward v.capacity==v.size() yields true**.  

Before C++11, there you could shrink the capacity only indirectly: Swapping the contents with another vector swaps the capacity. The following function shrinks the capacity while preserving the elements:  

```cpp
std::vector<T>(v).swap(v);
```

示例如下：  

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

输出如下：  

```md
capacity: 131072; size: 100000
capacity: 131072; size: 3
capacity: 3; size: 3
```

## vector的操作  

### 构建，复制和销毁  

|Operation |Effect |
:-:|:-:
|vector\<Elem\> c |Default constructor; creates an empty vector without any elements|
|vector\<Elem\> c(c2) |**Copy** constructor; creates a new vector as a copy of c2 (all elements are copied)|
|vector\<Elem\> c = c2 |**Copy** constructor; creates a new vector as a copy of c2 (all elements are copied)|
|vector\<Elem\> c(rv) |**Move** constructor; creates a new vector, taking the contents of the rvalue rv (since C++11)|
|vector\<Elem\> c = rv |**Move** constructor; creates a new vector, taking the contents of the rvalue rv (since C++11)|
|vector\<Elem\> c(n) |Creates a vector with **n elements** created **by the default constructor**|
|vector\<Elem\> c(n,elem) |Creates a vector initialized with n copies of element elem|
|vector\<Elem\> c(beg,end) |Creates a vector initialized with the elements of the range [beg,end)|
|vector\<Elem\> c(initlist) |Creates a vector initialized with the elements of **initializer list** initlist (since C++11)|
|vector\<Elem\> c = initlist |Creates a vector initialized with the elements of **initializer list** initlist (since C++11)|
|c.~vector()| Destroys all elements and frees the memory|

### 非更易型操作  

|Operation |Effect|
:-:|:-:
|c.empty() |Returns whether the container is empty (equivalent to size()==0 but might be faster)|
|c.size() |Returns the **current number of elements**|
|c.max_size() |Returns the maximum number of elements possible|
|c.capacity() |Returns the maximum possible number of elements without reallocation|
|c.reserve(num) |Enlarges capacity, if not enough yet|
|c.shrink_to_fit() |Request to reduce capacity to fit number of elements (since C++11)|
|c1 == c2 |Returns whether c1 is equal to c2 (calls == for the elements)|
|c1 != c2 |Returns whether c1 is not equal to c2 (equivalent to !(c1==c2))|  

### 赋值  

下表列出了“将新元素赋值给vector**并将旧元素全部移除**”的方法  

|Operation |Effect|
:-:|:-:
|c = c2 |Assigns all elements of c2 to c|
|c = rv |Move assigns all elements of the rvalue rv to c (since C++11)|
|c = initlist |Assigns all elements of the initializer list initlist to c (since C++11)|
|c.assign(n,elem) |Assigns n copies of element elem|
|c.assign(beg,end) |Assigns the elements of the range [beg,end)|
|c.assign(initlist) |Assigns all the elements of the initializer list initlist|
|c1.swap(c2) |Swaps the data of c1 and c2|
|swap(c1,c2) |Swaps the data of c1 and c2|  

### 元素访问  

The most important issue for the caller is whether these operations perform range checking. **Only at() performs range checking**. If the index is out of range, at() throws an out_of_range exception

|Operation| Effect|
:-:|:-:
|c[idx] |Returns the element with index idx (no range checking)|
|c.at(idx) |Returns the element with index idx (**throws range-error exception if idx is out of range**)|
|c.front() |Returns the first element (no check whether a first element exists)|
|c.back() |Returns the last element (no check whether a last element exists)|  

### 迭代器函数  

Vectors provide the usual operations to get iterators  

|Operation| Effect|
:-:|:-:
|c.begin() |Returns a **random-access iterator** for the first element|
|c.end() |Returns a **random-access iterator** for the position after the last element|
|c.cbegin() |Returns a **constant random-access iterator** for the first element (since C++11)|
|c.cend() |Returns a **constant random-access iterator** for the position after the last element (since C++11)|
|c.rbegin() |Returns a **reverse iterator** for the first element of a reverse iteration|
|c.rend() |Returns a **reverse iterator** for the position after the last element of a reverse iteration|
|c.crbegin() |Returns a **constant reverse iterator** for the first element of a reverse iteration (since C++11)|
|c.crend() |Returns a **constant reverse iterator** for the position after the last element of a reverse iteration (since C++11)|  

### 安插和移除元素  

|Operation |Effect|
:-:|:-:
|c.push_back(elem) |Appends a copy of elem at the end|
|c.pop_back() |Removes the last element (does not return it)|
|c.insert(pos,elem) |Inserts a copy of elem before iterator position pos and returns the position of the new element|
|c.insert(pos,n,elem) |Inserts n copies of elem before iterator position pos and returns the position of the first new element (or pos if there is no new element)|
|c.insert(pos,beg,end) |Inserts a copy of all elements of the range [beg,end) before iterator position pos and returns the position of the first new element (or pos if there is no new element)|
|c.insert(pos,initlist) |Inserts a copy of all elements of the initializer list initlist before iterator position pos and returns the position of the first new element (or pos if there is no new element; since C++11)|
|c.emplace(pos,args...) |Inserts a copy of an element initialized with args before iterator position pos and returns the position of the new element (since C++11)|
|c.emplace_back(args...) |Appends a copy of an element initialized with args at the end (returns nothing; since C++11)|
|c.erase(pos) |Removes the element at iterator position pos and returns the position of the next element|
|c.erase(beg,end)| Removes all elements of the range [beg,end) and returns the position of the next element|
|c.resize(num) |Changes the number of elements to num (if size() grows new elements are created by their **default constructor**)|
|c.resize(num,elem) |Changes the number of elements to num (if size() grows new elements are copies of elem)|
|c.clear() |Removes all elements (empties the container)|  

Vectors provide no operation to remove elements directly that have a certain value. You must use an algorithm to do this. For example, the following statement removes all elements that have the value val:  

```cpp
std::vector<Elem> coll;
...
// remove all elements with value val
coll.erase(remove(coll.begin(),coll.end(), val), coll.end());
```

## 基本操作示例  

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

## 测试迭代器是否支持随机访问  

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

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 7.3  
https://www.bilibili.com/video/BV1hb411j7mu  
