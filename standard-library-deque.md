# deque  

## 基本特性  

The abilities of deques **differ from those of vectors** as follows:  
• **Inserting and removing elements is fast at both the beginning and the end** (for vectors, it is fast only at the end). These operations are done in amortized constant time.  
• The internal structure has one more indirection to access the elements, so with deques, **element access and iterator movement are usually a bit slower**.  
• Deques provide **no support to control the capacity** and the moment of **reallocation**.  

The following features of vectors apply also to deques:  
• Inserting and deleting elements in the middle is relatively slow because all elements up to either end may be moved to make room or to fill a gap.  
• Iterators are **random-access iterators**.  

## deque的基本操作  

### 构造与拷贝  

|Operation| Effect|
:-:|:-:
|deque\<Elem\> c |Default constructor; creates an empty deque without any elements|
|deque\<Elem\> c(c2) |**Copy** constructor; creates a new deque as a copy of c2 (all elements are copied)|
|deque\<Elem\> c = c2 |**Copy** constructor; creates a new deque as a copy of c2 (all elements are copied)|
|deque\<Elem\> c(rv) |**Move** constructor; creates a new deque, taking the contents of the rvalue rv (since C++11)|
|deque\<Elem\> c = rv |**Move** constructor; creates a new deque, taking the contents of the rvalue rv (since C++11)|
|deque\<Elem\> c(n) |Creates a deque with n elements created by the default constructor|
|deque\<Elem\> c(n,elem) |Creates a deque initialized with n copies of element elem|
|deque\<Elem\> c(beg,end) |Creates a deque initialized with the elements of the range [beg,end)|
|deque\<Elem\> c(initlist) |Creates a deque initialized with the elements of **initializer list** initlist (since C++11)|
|deque\<Elem\> c = initlist |Creates a deque initialized with the elements of **initializer list** initlist (since C++11)|
|c.~deque() |Destroys all elements and frees the memory|

### 非更易型操作  

|Operation| Effect|
:-:|:-:
|c.empty() |Returns whether the container is empty (equivalent to size()==0 but might be faster)|
|c.size() |Returns the current number of elements|
|c.shrink_to_fit() |Request to reduce capacity to fit number of elements (since C++11)|
|c1 == c2 |Returns whether c1 is equal to c2 (calls == for the elements)|
|c1 != c2 |Returns whether c1 is not equal to c2 (equivalent to !(c1==c2))|
|||
|c[idx] |Returns the element with index idx (no range checking)|
|c.at(idx) |Returns the element with index idx (**throws range-error exception if idx is out of range**)|
|c.front() |Returns the **first** element (no check whether a first element exists)|
|c.back() |Returns the **last** element (no check whether a last element exists)|
|||
|c.begin() |Returns a **random-access iterator** for the first element|
|c.end() |Returns a **random-access iterator** for the position after the last element|
|c.cbegin() |Returns a **constant random-access iterator** for the first element (since C++11)|
|c.cend() |Returns a **constant random-access iterator** for the position after the last element (since C++11)|
|c.rbegin() |Returns a **reverse iterator** for the first element of a reverse iteration|
|c.rend() |Returns a **reverse iterator** for the position after the last element of a reverse iteration|
|c.crbegin() |Returns a **constant reverse iterator** for the first element of a reverse iteration (since C++11)|
|c.crend() |Returns a **constant reverse iterator** for the position after the last element of a reverse iteration (since C++11)|  

### 更易型操作  

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
|||
|c.push_back(elem) |Appends a copy of elem at the end|
|c.pop_back() |Removes the last element (does not return it)|
|c.push_front(elem) |Inserts a copy of elem at the beginning|
|c.pop_front() |Removes the first element (does not return it)|
|c.insert(pos,elem) |Inserts a copy of elem before iterator position pos and returns the position of the new element|
|c.insert(pos,n,elem) |Inserts n copies of elem before iterator position pos and returns the position of the first new element (or pos if there is no new element)
|c.insert(pos,beg,end) |Inserts a copy of all elements of the range [beg,end) before iterator position pos and returns the position of the first new element (or pos if there is no new element)
|c.insert(pos,initlist) |Inserts a copy of all elements of the initializer list initlist before iterator position pos and returns the position of the first new element (or pos if there is no new element; since C++11)|
|c.emplace(pos,args...)| Inserts a copy of an element initialized with args before iterator position pos and returns the position of the new element (since C++11)|
|c.emplace_back(args...)| Appends a copy of an element initialized with args at the end (returns nothing; since C++11)|
|c.emplace_front(args...) |Inserts a copy of an element initialized with args at the beginning (returns nothing; since C++11)|
|c.erase(pos)| Removes the element at iterator position pos and returns the position of the next element|
|c.erase(beg,end)| Removes all elements of the range [beg,end) and returns the position of the next element|
|c.resize(num) |Changes the number of elements to num (if size() grows new elements are created by their default constructor)|
|c.resize(num,elem) |Changes the number of elements to num (if size() grows new elements are copies of elem)|
|c.clear()| Removes all elements (empties the container)|

## 遍历  

```c++
void printDeque(const deque<int>& d)
{
    // const_iterator 只读迭代器，配合参数const deque<int>& d使用
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}
```

## 基本操作示例  

```c++
deque<int> dq;
dq.push_back(1);
dq.push_back(2);
dq.push_back(3);
dq.push_front(4);
printDeque(dq);

dq.pop_back();
dq.pop_front();
printDeque(dq); // 1 2

cout << dq.front() << endl; // 1
cout << dq.back() << endl; // 2
```

```c++
// 初始化
deque<int> d1(10, 100);
printDeque(d1); //100 100 100 100 100 100 100 100 100 100

// swap
deque<int> d2(5, 10);
d2.swap(d1);
printDeque(d2); //100 100 100 100 100 100 100 100 100 100

// 插入
d1.insert(d1.begin()++, 99);
printDeque(d1); // 99 10 10 10 10 10
d1.insert(++d1.begin(), 44);
printDeque(d1); // 99 44 10 10 10 10 10

//删除
d1.erase(d1.begin());
printDeque(d1); // 44 10 10 10 10 10
d1.erase(d1.begin(), d1.end());
printDeque(d1); // 等同于d1.clear()
```

## 排序  

```c++
deque<int> q;
q.push_back(60);
q.push_back(20);
q.push_back(30);
q.push_back(10);

// 升序排序
sort(q.begin(), q.end());
printDeque(q);  // 10 20 30 60

// 降序排序
sort(q.begin(), q.end(), cmp);
printDeque(q);  // 60 30 20 10
```

```c++
// 比较器
bool cmp(int v1, int v2)
{
    return v1 > v2;
}
```

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 7.4  
https://www.bilibili.com/video/BV1hb411j7mu  
