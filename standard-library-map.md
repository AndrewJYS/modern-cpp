# map & multimap  

## 概述  

Maps and multimaps are containers that manage key/value pairs as elements. These containers sort their elements automatically, according to a certain sorting criterion that is used for the key. The difference between the two is that multimaps allow duplicates, whereas maps do not.  

the types are defined as class templates inside namespace std:  

```cpp
namespace std {
template <typename Key, typename T,
         typename Compare = less<Key>,
         typename Allocator = allocator<pair<const Key,T> > >
        class map;

template <typename Key, typename T,
          typename Compare = less<Key>,
          typename Allocator = allocator<pair<const Key,T> > >
        class multimap;
}
```

The first template parameter is the type of the element’s key, and the second template parameter is the type of the element’s associated value. The elements of a map or a multimap may have any types Key and T that meet the following two requirements:  
1.Both key and value must be copyable or movable.  
2.The key must be comparable with the sorting criterion.  
Note that the element type (value_type) is a pair \<const Key, T\>.  
The optional **third template parameter defines the sorting criterion**.  

You **may not change the key of an element directly**, because doing so might compromise the correct order. **To modify the key of an element, you must remove the element that has the old key and insert a new element that has the new key and the old value**. As a consequence, from the iterator’s point of view, **the element’s key is constant**. However, **a direct modification of the value of the element is still possible**, provided that the type of the value is not constant.  

## 基本操作  

### 创建，赋值和销毁  

|Operation |Effect|
:-:|:-:
|map c |Default constructor; creates an empty map/multimap without any elements|
|map c(op) |Creates an empty map/multimap that uses op as the sorting criterion|
|map c(c2) |**Copy** constructor; creates a copy of another map/multimap of the same type (all elements are copied)|
|map c = c2 |**Copy** constructor; creates a copy of another map/multimap of the same type (all elements are copied)|
|map c(rv) |**Move** constructor; creates a new map/multimap of the same type, taking the contents of the rvalue rv (since C++11)|
|map c = rv| **Move** constructor; creates a new map/multimap of the same type, taking the contents of the rvalue rv (since C++11)|
|map c(beg,end) |Creates a map/multimap initialized by the elements of the range [beg,end)|
|map c(beg,end,op) |Creates a map/multimap with the sorting criterion op initialized by the elements of the range [beg,end)|
|map c(initlist) |Creates a map/multimap initialized with the elements of **initializer list** initlist (since C++11)|
|map c = initlist |Creates a map/multimap initialized with the elements of **initializer list** initlist (since C++11)|
|c.~map() |Destroys all elements and frees the memory|

### 非更易型操作  

|Operation| Effect|
:-:|:-:
|c.key_comp() |Returns the comparison criterion|
|c.value_comp() |Returns the comparison criterion for values as a whole (an object that compares the key in a key/value pair)|
|c.empty() |Returns whether the container is empty (equivalent to size()==0 but might be faster)|
|c.size() |Returns the current number of elements|
|c.max_size() |Returns the maximum number of elements possible|
|c1 == c2 |Returns whether c1 is equal to c2 (calls == for the elements)|
|c1 != c2 |Returns whether c1 is not equal to c2 (equivalent to !(c1==c2))|

### 特殊查找操作  

|Operation| Effect|
:-:|:-:
|c.count(val) |Returns the number of elements with key val|
|c.find(val) |Returns the position of the first element with key val (or end() if none found)|
|c.lower_bound(val) |Returns the first position where an element with key val would get inserted (the first element with a key >= val)|
|c.upper_bound(val)| Returns the last position where an element with key val would get inserted (the first element with a key > val)|
|c.equal_range(val) |Returns a range with all elements with a key equal to val (i.e., the first and last positions, where an element with key val would get inserted)|

**You can’t use the find() member function to search for an element that has a certain value**.  

### 赋值  

|Operation |Effect|
:-:|:-:
|c = c2 |Assigns all elements of c2 to c|
|c = rv |Move assigns all elements of the rvalue rv to c (since C++11)|
|c = initlist |Assigns all elements of the initializer list initlist to c (since C++11)|
|c1.swap(c2) |Swaps the data of c1 and c2|
|swap(c1,c2) |Swaps the data of c1 and c2|

### 迭代器函数和元素访问  

|Operation| Effect|
:-:|:-:
|c.begin()| Returns a bidirectional iterator for the first element|
|c.end()|Returns a bidirectional iterator for the position after the last element|
|**c.cbegin()** |Returns a constant bidirectional iterator for the first element (since C++11)|
|**c.cend()** |Returns a constant bidirectional iterator for the position after the last element (since C++11)|
|c.rbegin() |Returns a reverse iterator for the first element of a reverse iteration|
|c.rend() |Returns a reverse iterator for the position after the last element of a reverse iteration|
|**c.crbegin()**| Returns a constant reverse iterator for the first element of a reverse iteration (since C++11)|
|**c.crend()** |Returns a constant reverse iterator for the position after the last element of a reverse iteration (since C++11)|

More important is the constraint that the **key of all elements inside a map and a multimap is considered to be constant**. Thus, the type of the elements is pair\<const Key, T\>. This is necessary to ensure that you **can’t** compromise the order of the elements by **changing their keys**. However, you **can’t call any modifying algorithm if the destination is a map or a multimap**. **For example, you can’t call the remove() algorithm**, because it “removes” by overwriting “removed” elements with the following elements. **To remove elements in maps and multimaps, you can use only member functions provided by the container**.  

If you use algorithms and lambdas to operate with the elements of a map, you explicitly have to declare the element type:  

```cpp
std::map<std::string,float> coll;
...
// add 10 to the value of each element:
std::for_each (coll.begin(), coll.end(),
               [] (std::pair<const std::string,float>& elem) {
                   elem.second += 10;
               });
```

Instead of using the following:  

```cpp
std::pair<const std::string,float>
```

you could use  

```cpp
std::map<std::string,float>::value_type
```

or  

```cpp
decltype(coll)::value_type
```

### 元素安插与移除  

|Operation |Effect|
:-:|:-:
|c.insert(val) |Inserts a copy of val and returns the position of the new element and, for maps, whether it succeeded|
|c.insert(pos,val) |Inserts a copy of val and returns the position of the new element (pos is used as a hint pointing to where the insert should start the search)|
|c.insert(beg,end)| Inserts a copy of all elements of the range [beg,end) (returns nothing)|
|c.insert(initlist) |Inserts a copy of all elements in the initializer list initlist (returns nothing; since C++11)|
|c.emplace(args...) |Inserts a copy of an element initialized with args and returns the position of the new element and, for maps, whether it succeeded (since C++11)|
|c.emplace_hint(pos,args...) |Inserts a copy of an element initialized with args and returns the position of the new element (pos is used as a hint pointing to where the insert should start the search)|
|c.erase(val)| **Removes all elements equal to val** and returns the number of removed elements|
|c.erase(pos) |Removes the element at iterator position pos and returns the following position (returned nothing before C++11)|
|c.erase(beg,end) |Removes all elements of the range [beg,end) and returns the following position (returned nothing before C++11)|
|c.clear() |Removes all elements (empties the container)|

**When removing elements, be careful not to saw off the branch on which you are sitting**. There is a big danger that you will remove an element to which your iterator is referring. For example:  

```cpp
std::map<std::string,float> coll;
...
for (auto pos = coll.begin(); pos != coll.end(); ++pos) {
    if (pos->second == value) {
        coll.erase(pos); // RUNTIME ERROR !!!
    }
}
```

Calling erase() for the element to which you are referring with pos invalidates pos as an iterator of coll. Thus, if you use pos after removing its element without any reinitialization, all bets are off.  

Since C++11, a solution is easy because erase() always returns the value of the following element:  

```cpp
std::map<std::string,float> coll;
...
for (auto pos = coll.begin(); pos != coll.end(); ) {
    if (pos->second == value) {
        pos = coll.erase(pos); // possible only since C++11
    }
    else {
        ++pos;
    }
}
```

## 遍历  

```c++
void printMap(map<int, int>& m)
{
    for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout << "(" << (*it).first << ", " << (*it).second << ")";
    }
    cout << endl;
}
```

## 基本操作示例  

```c++
map<int, int> m;

// 插入
m.insert(pair<int, int>(1, 10));
m.insert(make_pair(2, 20));
m.insert(map<int, int>::value_type(3, 30));
m[4] = 40;
printMap(m); // (1, 10)(2, 20)(3, 30)(4, 40) 默认key从小到大排序

// 按照key值删除元素
m.erase(3);
printMap(m); // (1, 10)(2, 20)(4, 40)

// 查找
map<int, int>::iterator pos = m.find(3);
if (pos != m.end())
    cout << "(" << (*pos).first << ", " << (*pos).second << ")";
else
    cout << "not found" << endl; // 输出not found

// 统计, count()返回0或1
int num = m.count(4);
cout << num << endl; // 1

// lower_bound(keyElem), 返回第一个key >= keyElem的元素的迭代器，找不到则返回end()
map<int, int>::iterator low = m.lower_bound(2);
// 下述例子输出 lower bound is 2
if (low != m.end())
    cout << "lower bound is " << (*low).first << endl;
else
    cout << "lower bound not found" << endl;


// upper_bound(keyElem), 返回第一个key > keyElem的元素的迭代器，找不到则返回end()
map<int, int>::iterator upp = m.upper_bound(2);
// 下述例子输出 upper bound is 4
if (upp != m.end())
    cout << "upper bound is " << (*upp).first << endl;
else
    cout << "upper bound not found" << endl;


// equal_range(keyElem) 返回pair<lower_bound(keyElem), upper_bound(keyElem)>
pair<map<int, int>::iterator, map<int, int>::iterator> it = m.equal_range(2);
if (it.first != m.end())
    cout << "lower bound is " << (*(it.first)).first << endl;
else
    cout << "lower bound not found" << endl;
if (it.second != m.end())
    cout << "upper bound is " << (*(it.second)).first << endl;
else
    cout << "upper bound not found" << endl;
```

## 仿函数改变map的排序规则  

```c++
void test2()
{
    map<int, int, MyCMP> m;
    m.insert(pair<int, int>(1, 10));
    m.insert(make_pair(2, 20));
    m.insert(map<int, int>::value_type(3, 30));
    m[4] = 40;

    for (map<int, int, MyCMP>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout << "(" << (*it).first << ", " << (*it).second << ")";
    }
    cout << endl; // (4, 40)(3, 30)(2, 20)(1, 10)
}
```

```c++
//仿函数

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

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 7.8  
https://www.bilibili.com/video/BV1hb411j7mu  
