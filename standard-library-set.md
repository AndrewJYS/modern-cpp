# set & multiset  

## 概述  

Set and multiset containers sort their elements automatically according to a certain sorting criterion. The difference between the two types of containers is that multisets allow duplicates, whereas sets do not.  

the types are defined as class templates inside namespace std:  

```cpp
namespace std {
    template <typename T,
              typename Compare = less<T>,
              typename Allocator = allocator<T> >
            class set;

    template <typename T,
              typename Compare = less<T>,
              typename Allocator = allocator<T> >
            class multiset;
}
```

The optional second template argument defines the sorting criterion.  

automatic sorting also imposes an important constraint on sets and multisets: You may not change the value of an element directly, because doing so might compromise the correct order. (set中的迭代器是const迭代器，也就是说，不能通过set的迭代器修改对应的值)  
Therefore, **to modify the value of an element**, you must **remove the element having the old value and insert a new element that has the new value**. The interface reflects this behavior:  
• Sets and multisets don’t provide operations for direct element access.  
• Indirect access via iterators has the constraint that, from the iterator’s point of view, the element value is constant.  

## 基本操作  

### 创建，复制和销毁  

|Operation |Effect|
:-:|:-:
|set c |Default constructor; creates an empty set/multiset without any elements|
|set c(op) |Creates an empty set/multiset that **uses op as the sorting criterion**|
|set c(c2) |**Copy** constructor; creates a copy of another set/multiset of the same type (all elements are copied)|
|set c = c2 |**Copy** constructor; creates a copy of another set/multiset of the same type (all elements are copied)|
|set c(rv) |**Move** constructor; creates a new set/multiset of the same type, taking the contents of the rvalue rv (since C++11)|
|set c = rv |**Move** constructor; creates a new set/multiset of the same type, taking the contents of the rvalue rv (since C++11)|
|set c(beg,end) |Creates a set/multiset initialized by the elements of the range [beg,end)|
|set c(beg,end,op) |Creates a set/multiset with the sorting criterion op initialized by the elements of the range [beg,end)|
|set c(initlist) |Creates a set/multiset initialized with the elements of **initializer list** initlist (since C++11)|
|set c = initlist |Creates a set/multiset initialized with the elements of **initializer list** initlist (since C++11)|
|c.~set() |Destroys all elements and frees the memory|  

### 非更易型操作  

|Operation |Effect|
:-:|:-:
|c.key_comp() |Returns the comparison criterion|
|c.value_comp() |Returns the comparison criterion for values as a whole (same as key_comp())|
|c.empty() |Returns whether the container is empty (equivalent to size()==0 but might be faster)|
|c.size() |Returns the current number of elements|
|c.max_size() |Returns the maximum number of elements possible|
|c1 == c2 |Returns whether c1 is equal to c2 (calls == for the elements)|
|c1 != c2 |Returns whether c1 is not equal to c2 (equivalent to !(c1==c2))|

**Comparisons are provided only for containers of the same type**. Thus, **the elements and the sorting criterion must have the same types**; otherwise, a type error occurs at compile time.  

### 特殊的查找函数  

These functions are special versions of general algorithms that have the same name. You should always **prefer the optimized versions** for sets and multisets to achieve logarithmic complexity instead of the linear complexity of the general algorithms.  

|Operation| Effect|
:-:|:-:
|c.count(val)| Returns the number of elements with value val|
|c.find(val) |Returns the position of the first element with value val (or end() if none found)|
|c.lower_bound(val) |Returns the first position, where val would get inserted (the first element >= val)|
|c.upper_bound(val) |Returns the last position, where val would get inserted (the first element > val)|
|c.equal_range(val) |Returns a range with all elements with a value equal to val (i.e., the first and last position, where val would get inserted)|

If lower_bound() or the first value of equal_range() is equal to upper_bound() or the second value of equal_range(), no elements with the same value exist in the set or multiset.  

### 赋值  

|Operation| Effect|
:-:|:-:
|c = c2 |Assigns all elements of c2 to c|
|c = rv |Move assigns all elements of the rvalue rv to c (since C++11)|
|c = initlist |Assigns all elements of the initializer list initlist to c (since C++11)|
|c1.swap(c2) |Swaps the data of c1 and c2|
|swap(c1,c2) |Swaps the data of c1 and c2|

### 迭代器相关函数  

from an iterator’s point of view, **all elements are considered constant**. This is necessary to ensure that you **can’t** compromise the order of the elements by **changing their values**. However, as a result, you **can’t call any modifying algorithm** on the elements of a set or a multiset. **For example, you can’t call the remove() algorithm**, because it “removes” by overwriting “removed” elements with the following elements. **To remove elements in sets and multisets, you can use only member functions provided by the container**.  

|Operation| Effect|
:-:|:-:
|c.begin() |Returns a bidirectional iterator for the first element|
|c.end() |Returns a bidirectional iterator for the position after the last element|
|**c.cbegin()** |Returns a **constant bidirectional iterator** for the first element (since C++11)|
|**c.cend()** |Returns a **constant bidirectional iterator** for the position after the last element (since C++11)|
|c.rbegin() |Returns a reverse iterator for the first element of a reverse iteration|
|c.rend() |Returns a reverse iterator for the position after the last element of a reverse iteration|
|**c.crbegin()** |Returns a **constant reverse iterator** for the first element of a reverse iteration (since C++11)|
|**c.crend()** |Returns a **constant reverse iterator** for the position after the last element of a reverse iteration (since C++11)|

### Inserting and Removing Elements  

|Operation| Effect|
:-:|:-:
|c.insert(val) |Inserts a copy of val and returns the position of the new element and, for sets, whether it succeeded|
|c.insert(pos,val) |Inserts a copy of val and returns the position of the new element (pos is used as a hint pointing to where the insert should start the search)|
|c.insert(beg,end) |Inserts a copy of all elements of the range [beg,end) (returns nothing)|
|c.insert(initlist) |Inserts a copy of all elements in the initializer list initlist (returns nothing; since C++11)|
|c.emplace(args...) |Inserts a copy of an element initialized with args and returns the position of the new element and, for sets, whether it succeeded (since C++11)|
|c.emplace_hint(pos,args...) |Inserts a copy of an element initialized with args and returns the position of the new element (pos is used as a hint pointing to where the insert should start the search)|
|**c.erase(val)** |**Removes all elements equal to val** and returns the number of removed elements|
|c.erase(pos) |Removes the element at iterator position pos and returns the following position (returned nothing before C++11)|
|c.erase(beg,end) |Removes all elements of the range [beg,end) and returns the following position (returned nothing before C++11)|
|c.clear() |Removes all elements (empties the container)|

## 遍历  

```c++
void printSet(const set<int>& S)
{
    for (set<int>::const_iterator it = S.begin(); it != S.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}
```

## 基本操作示例  

```c++
set<int> s;
s.insert(1);
s.insert(6);
s.insert(5);
s.insert(8);


// 插入
pair<set<int>::iterator, bool> it = s.insert(8);
if (it.second)
    cout << "insert successfully" << endl;
else
    cout << "fail to insert" << endl;  // 输出fail to insert


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
```

## 仿函数改变set的排序规则  

```c++
set<int> s {1,6,5,4,8}; // set是自带从小到大排序的  
printSet(s); // 1 4 5 6 8

s.erase(6);
printSet(s);  // 1 4 5 8

// 插入之前指定从大到小排序
set<int, MyCMP> newS {1,6,5,4,8};

for (set<int, MyCMP>::iterator it = newS.begin(); it != newS.end(); it++)
{
    cout << *it << " "; // 8 6 5 4 1
}
cout << endl;
```

```c++
// 仿函数（这里不能使用比较器，否则不匹配，会报错）

class MyCMP
{
public:
    bool operator()(int v1, int v2)
    {
        return v1 > v2;
    }
};
```

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 7.7  
https://www.bilibili.com/video/BV1hb411j7mu  
