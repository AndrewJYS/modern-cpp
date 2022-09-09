# list  

## 基本特性  

A list (an instance of the container class list<>) manages its elements as a doubly linked list  

a list differs in several major ways from arrays, vectors, and deques:  
• A list does **not provide random access**. Thus, accessing an arbitrary element using a list is slow. However, you can navigate through the list from both end. So accessing both the first and the last elements is fast. Lists **provide neither a subscript operator nor at()**, because no random access is provided.  
• **Inserting and removing elements is fast at each position** (provided you are there), and not only at one or both ends. You can always insert and delete an element in constant time, because no other elements have to be moved. Internally, only some pointer values are manipulated.  
• Inserting and deleting elements does not invalidate pointers, references, and iterators to other elements.  
• Lists don’t provide operations for capacity or reallocation  

## list的基本操作  

### 创建，复制，销毁  

|Operation| Effect|
:-:|:-:
|list\<Elem\> c |Default constructor; creates an empty list without any elements|
|list\<Elem\> c(c2) |**Copy** constructor; creates a new list as a copy of c2 (all elements are copied)|
|list\<Elem\> c = c2 |**Copy** constructor; creates a new list as a copy of c2 (all elements are copied)|
|list\<Elem\> c(rv) |**Move** constructor; creates a new list, taking the contents of the rvalue rv (since C++11)|
|list\<Elem\> c = rv |**Move** constructor; creates a new list, taking the contents of the rvalue rv (since C++11)|
|list\<Elem\> c(n) |Creates a list with n elements created by the default constructor|
|list\<Elem\> c(n,elem) |Creates a list initialized with n copies of element elem|
|list\<Elem\> c(beg,end) |Creates a list initialized with the elements of the range [beg,end)|
|list\<Elem\> c(initlist) |Creates a list initialized with the elements of **initializer list** initlist (since C++11)|
|list\<Elem\> c = initlist |Creates a list initialized with the elements of **initializer list** initlist (since C++11)|
|c.~list() |Destroys all elements and frees the memory|

### 非更易型操作  

|Operation| Effect|
:-:|:-:
|c.empty() |Returns whether the container is empty (equivalent to size()==0 but might be faster)|
|c.size() |Returns the current number of elements|
|c1 == c2 |Returns whether c1 is equal to c2 (calls == for the elements)|
|c1 != c2 |Returns whether c1 is not equal to c2 (equivalent to !(c1==c2))|

### 赋值  

|Operation| Effect|
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

|Operation| Effect|
:-:|:-:
|c.front() |Returns the first element (no check whether a first element exists)|
|c.back() |Returns the last element (no check whether a last element exists)|

### 迭代器相关函数  

you can’t call algorithms that require random-access iterators. All algorithms that manipulate the order of elements a lot, especially sorting algorithms, are in this category. However, for sorting the elements, lists provide the special member function sort()  

|Operation| Effect|
:-:|:-:
|c.begin() |Returns a **bidirectional iterator** for the **first** element|
|c.end() |Returns a **bidirectional iterator** for the position **after the last** element|
|c.cbegin() |Returns a **constant bidirectional iterator** for the **first** element (since C++11)|
|c.cend() |Returns a **constant bidirectional iterator** for the position **after the last** element (since C++11)|
|c.rbegin() |Returns a **reverse iterator** for the first element of a reverse iteration|
|c.rend() |Returns a **reverse iterator** for the position after the last element of a reverse iteration|
|c.crbegin() |Returns a **constant reverse iterator** for the first element of a reverse iteration (since C++11)|
|c.crend() |Returns a **constant reverse iterator** for the position after the last element of a reverse iteration (since C++11)|

### 元素的安插和删除  

For **removing elements**, **lists provide** special implementations of the **remove()** algorithms. **These member functions are faster than the remove() algorithms** because they manipulate only internal pointers rather than the elements.  

You can use **remove_if()** to define the criterion for the removal of the elements **by a function or a function object**. remove_if() removes each element for which calling the passed operation yields true.  

|Operation| Effect|
:-:|:-:
|c.push_back(elem) |**Appends** a copy of elem at the **end**|
|c.pop_back() |**Removes** the **last** element (does not return it)|
|c.push_front(elem) |**Inserts** a copy of elem at the **beginning**|
|c.pop_front()| **Removes** the **first** element (does not return it)|
|c.insert(pos,elem) |Inserts a copy of elem before iterator position pos and returns the position of the new element|
|c.insert(pos,n,elem) |Inserts n copies of elem before iterator position pos and returns the position of the first new element (or pos if there is no new element)|
|c.insert(pos,beg,end) |Inserts a copy of all elements of the range [beg,end) before iterator position pos and returns the position of the first new element (or pos if there is no new element)|
|c.insert(pos,initlist) |Inserts a copy of all elements of the initializer list initlist before iterator position pos and returns the position of the first new element (or pos if there is no new element; since C++11)|
|c.emplace(pos,args...) |Inserts a copy of an element initialized with args before iterator position pos and returns the position of the new element (since C++11)|
|c.emplace_back(args...) |Appends a copy of an element initialized with args at the end (returns nothing; since C++11)|
|c.emplace_front(args...) |Inserts a copy of an element initialized with args at the beginning (returns nothing; since C++11)|
|c.erase(pos) |Removes the element at iterator position pos and returns the position of the next element|
|c.erase(beg,end) |Removes all elements of the range [beg,end) and returns the position of the next element|
|**c.remove(val)** |Removes all elements with value val|
|**c.remove_if(op)** |Removes all elements for which op(elem) yields true|
|c.resize(num) |Changes the number of elements to num (if size() grows new elements are created by their default constructor)|
|c.resize(num,elem)| Changes the number of elements to num (if size() grows new elements are copies of elem)|
|c.clear() |Removes all elements (empties the container)|

### splice函数以及会改变元素次序的函数  

|Operation| Effect|
:-:|:-:
|c.unique() |Removes duplicates of consecutive elements with the same value|
|c.unique(op) |Removes duplicates of consecutive elements, for which op() yields true|
|c.splice(pos,c2) |Moves all elements of c2 to c in front of the iterator position pos|
|c.splice(pos,c2,c2pos) |Moves the element at c2pos in c2 in front of pos of list c (c and c2 may be identical)
|c.splice(pos,c2, c2beg,c2end) |Moves all elements of the range [c2beg,c2end) in c2 in front of pos of list c (c and c2 may be identical)|
|c.sort() |Sorts all elements with operator <|
|c.sort(op) |Sorts all elements with op()|
|c.merge(c2) |Assuming that **both containers contain the elements sorted**, moves all elements of c2 into c so that all elements are merged and still sorted
|c.merge(c2,op) |Assuming that **both containers contain the elements sorted due to the sorting criterion op()**, moves all elements of c2 into c so that all elements are merged and still sorted according to op()
|c.reverse() |Reverses the order of all elements

```cpp
list<int> L1 {1,4,4,4,5,6,7,7};
L1.unique();
for_each(L1.cbegin(), L1.cend(), [](int val){ cout << val << " "; });
cout << endl;
//1 4 5 6 7

list<int> L2 {1,5,6,7,8,9,4,10,11};
L2.unique(cmp);
for_each(L2.cbegin(), L2.cend(), [](int val){ cout << val << " "; });
cout << endl;
// 1 5 4
```

```cpp
list<int> L1 {1,4,5,6};
list<int> L2 {2,5,6,8};
L1.merge(L2);
for_each(L1.cbegin(), L1.cend(), [](int val){ cout << val << " "; });
cout << endl;
// 1 2 4 5 5 6 6 8

list<int> L3 {6,5,4,1};
list<int> L4 {8,6,5,2};
L3.merge(L4);
for_each(L3.cbegin(), L3.cend(), [](int val){ cout << val << " "; });
cout << endl;
// 6 5 4 1 8 6 5 2，逆序不行

list<int> L5 {1,4,5,6};
list<int> L6 {2,5,6,8};
L5.merge(L6, less<int>());
for_each(L5.cbegin(), L5.cend(), [](int val){ cout << val << " "; });
cout << endl;
//1 2 4 5 5 6 6 8,  op要与L5,L6的排序op相同

list<int> L7 {6,5,4,1};
list<int> L8 {8,6,5,2};
L7.merge(L8, greater<int>());
for_each(L7.cbegin(), L7.cend(), [](int val){ cout << val << " "; });
cout << endl;
//8 6 6 5 5 4 2 1
```

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

## 基本操作示例  

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

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 7.5  
https://www.bilibili.com/video/BV1hb411j7mu  
