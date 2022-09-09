# introduction to STL  

## STL组件  

STL从广义上分为：**容器，算法和迭代器**，迭代器是沟通的桥梁，使容器和算法之间可以进行无缝连接。  
容器：用来管理某类对象的集合  
迭代器：用来在一个对象集合内遍历元素  
算法：用来处理集合内的元素  

STL还有更泛化的组件，借由特定的适配器和函数对象，你可以补充，约束或定制算法以满足特别的需求  

## 容器  

There are three general kinds of containers:  
**1.Sequence containers** are **ordered collections** in which every element has a certain position. This position depends on the time and place of the insertion, but it is independent of the value of the element. The STL contains five predefined sequence container classes: **array, vector, deque, list, and forward_list**.  
**2.Associative containers** are **sorted collections** in which the position of an element depends on its value (or key, if it’s a key/value pair) due to a certain sorting criterion. The STL contains four predefined associative container classes: **set, multiset, map, and multimap**.  
**3.Unordered (associative) containers** are unordered collections in which the position of an element doesn’t matter. **The only important question is whether a specific element is in such a
collection**. The STL contains four predefined unordered container classes: **unordered_set, unordered_multiset, unordered_map, and unordered_multimap**.  

• **Sequence containers** are usually implemented as **arrays or linked lists**.  
• **Associative containers** are usually implemented as **binary trees**.  
• **Unordered containers** are usually implemented as **hash tables**.  

### Container Adapters  

In addition to the fundamental container classes, the C++ standard library provides so-called container adapters, which are predefined containers that provide a restricted interface to meet special needs.  

• A **stack** (the name says it all) manages its elements by the **LIFO** (last-in-first-out) policy.  
• A **queue** manages its elements by the **FIFO** (first-in-first-out) policy. That is, it is an ordinary buffer.  
• A **priority queue** is a container in which the elements may have different priorities. The priority is based on a sorting criterion that the programmer may provide (by default, operator < is used). A priority queue is, in effect, a buffer in which the next element is always one having the highest priority inside the queue. If more than one element has the highest priority, the order of these elements is undefined.  

## iterator  

An iterator is an object that can iterate over elements (navigate from element to element).  
The following fundamental operations define the behavior of an iterator:  
• **Operator \*** returns the element of the current position. If the elements have members, you can use operator -> to access those members directly from the iterator.  
• **Operator ++** lets the iterator step forward to the next element. Most iterators also allow stepping backward by using operator --.  
• **Operators == and !=** return whether two iterators represent the same position.  
• **Operator =** assigns an iterator (the position of the element to which it refers).  

**each container type supplies its own kind of iterator**. As a result, iterators share the same interface but have different types.  

**All container classes provide the same basic member functions that enable them to use iterators to navigate over their elements**. The **most important** of these functions are as follows:  
• **begin()** returns an iterator that represents the beginning of the elements in the container. The beginning is the position of the first element, if any.  
• **end()** returns an iterator that represents the end of the elements in the container. The end is the position behind the last element. Such an iterator is also called a past-the-end iterator.  

Thus, **begin() and end() define a half-open range** that includes the first element but excludes the last. A **half-open range has two advantages**:  
1.You have a simple end criterion for loops that iterate over the elements: They simply continue as long as end() is not reached.  
2.It avoids special handling for empty ranges. For empty ranges, begin() is equal to end().  

every container defines two iterator types:  
1.container::iterator is provided to iterate over elements in read/write mode.  
2.container::const_iterator is provided to iterate over elements in read-only mode.  

### iterator category  

The iterators of the predefined container classes belong to one of the following three categories:  
1.**Forward iterators** are able to iterate **only forward**, using the **increment operator**. The iterators of the class forward_list are forward iterators. The iterators of the container classes unordered_set, unordered_multiset, unordered_map, and unordered_multimap are “at least” forward iterators.  
2.**Bidirectional iterators** are able to **iterate in two directions**: **forward**, by using the increment operator, and **backward**, by using the decrement operator. **The iterators of the container classes list, set, multiset, map, and multimap are bidirectional iterators**.  
3.**Random-access iterators** have all the properties of bidirectional iterators. In addition, they can perform **random access**. In particular, they **provide operators for iterator arithmetic** (in accordance with pointer arithmetic of an ordinary pointer). You can add and subtract offsets, process differences, and compare iterators by using relational operators, such as < and >. **The iterators of the container classes vector, deque, array, and iterators of strings are random access iterators**.  

In addition, two other iterator categories are defined:  
• **Input iterators** are able to **read**/process some values **while iterating forward**. **Input stream iterators are an example of such iterators**.  
• **Output iterators** are able to **write** some values **while iterating forward**. **Inserters and output stream iterators are examples of such iterators**.  

## iterator adapter  

The C++ standard library provides several predefined special iterators: iterator adapters. They are more than auxiliary classes; they give the whole concept a lot more power.  

### Insert iterators  

Insert iterators, or inserters, are used to let algorithms operate in insert mode rather than in overwrite mode. In particular, inserters **solve the problem of algorithms that write to a destination that does not have enough room: They let the destination grow accordingly**.  

```cpp
list<int> coll1 {1,2,3,4,5,6,7};

vector<int> coll2;
copy(coll1.cbegin(), coll1.cend(), back_inserter(coll2));
for_each(coll2.cbegin(), coll2.cend(), [](int val){ cout << val << " "; });
cout << endl; // 1 2 3 4 5 6 7

deque<int> coll3;
copy(coll1.cbegin(), coll1.cend(), front_inserter(coll3));
for_each(coll3.cbegin(), coll3.cend(), [](int val){ cout << val << " "; });
cout << endl; // 7 6 5 4 3 2 1

set<int> coll4;
copy(coll1.cbegin(), coll1.cend(), inserter(coll4, coll4.begin()));
for_each(coll4.cbegin(), coll4.cend(), [](int val){ cout << val << " "; });
cout << endl; // 1 2 3 4 5 6 7
```

|Expression| Kind of Inserter|
:-:|:-:
|back_inserter(container)| Appends in the same order by using push_back(val). **Back inserters** insert the elements at the back of their container (appends them) by **calling push_back()**. back inserters can be **used only for containers that provide push_back() as a member function**. In the C++ standard library, these containers are vector, **deque, list, and strings**.|
|front_inserter(container) |Inserts at the front in reverse order by using push_front(val). **Front inserters** insert the elements at the front of their container by **calling push_front()**. Front inserters can be **used only for containers that provide push_front() as a member function**. In the C++ standard library, these containers are **deque, list, and forward_list**.|
|inserter(container,pos)| Inserts at pos (in the same order) by using insert(pos,val). **General inserters**, or simply inserters, **insert elements directly in front of the position that is passed as the second argument of its initialization**. A general inserter **calls the insert() member function** with the new value and the new position as arguments. Note that **all predefined containers except array and forward_list have such an insert() member function**. Thus, **this is the only predefined inserter for associative and unordered containers**.|

### Stream iterators  

**Stream iterators read from or write to a stream**. Thus, they provide an abstraction that lets the input from the keyboard behave as a collection from which you can read. Similarly, you can redirect the output of an algorithm directly into a file or onto the screen.  

```cpp
vector<string> coll;

// read all words from the standard input
// - source: all strings until end-of-file (or error)
// - destination: coll (inserting)
copy (istream_iterator<string>(cin), // start of source
      istream_iterator<string>(),    // end of source
      back_inserter(coll));          // destination

// sort elements
sort (coll.begin(), coll.end());

// print all elements without duplicates
// - source: coll
// - destination: standard output (with newline between elements)
unique_copy (coll.cbegin(), coll.cend(),            // source
             ostream_iterator<string>(cout, " "));  // destination
```

```md
输入：1 2 3 4 5 6 6 6 6 6 7
输出：1 2 3 4 5 6 7
```

The expression  

```cpp
istream_iterator<string>(cin)
```

**creates a stream iterator** that **reads from the standard input stream cin**. The template argument string specifies that the stream iterator reads elements of this type. These elements are read with the usual input operator >>. Thus, each time the algorithm wants to process the next element, the istream iterator transforms that desire into a call of  

```cpp
cin >> string
```

The expression  

```cpp
istream_iterator<string>()
```

**calls the default constructor of istream iterators that creates a so-called end-of-stream iterator**. It represents a stream from which you can no longer read. As usual, **the copy() algorithm operates as long as the (incremented) first argument differs from the second argument. The end-of-stream iterator is used as the end of the range**, so the algorithm reads all strings from cin until it can no longer read any more (owing to end-of-stream or an error). To summarize, the source of the algorithm is “all words read from cin.” These words are copied by inserting them into coll with the help of a back inserter.  

the statement  

```cpp
unique_copy (coll.cbegin(), coll.cend(),
             ostream_iterator<string>(cout,"\n"));
```

copies all elements from the collection into the destination cout. During this process, the unique_copy() algorithm **eliminates adjacent duplicate values**. The expression  

```cpp
ostream_iterator<string>(cout,"\n")
```

**creates an output stream iterator** that writes strings to cout by calling operator << for each element. The second argument behind cout is optional and serves as a separator between the elements. In this example, it is a newline character, so every element is written on a separate line.  

### Reverse iterators  

Reverse iterators let algorithms operate backward by switching the call of an increment operator internally into a call of the decrement operator, and vice versa. **All containers with bidirectional iterators or random-access iterators** (all sequence containers except forward_list and all associative containers) **can create reverse iterators via their member functions rbegin() and rend()**. Since C++11, the corresponding member functions returning **read-only iterators, crbegin() and crend()**, are also provided.  

## algorithm  

**Algorithms are not member functions** of the container classes but instead are **global functions** that operate with iterators. This has an important advantage: Instead of each algorithm being implemented for each container type, all are implemented only once for any container type.  

**Every algorithm processes half-open ranges**. Thus, a range is defined so that it includes the position used as the beginning of the range but excludes the position used as the end. This concept is often described by using the traditional mathematical notations for half-open ranges: **[begin,end)**  

**Several algorithms process more than one range**. In this case, you usually **must define both the beginning and the end only for the first range. For all other ranges, you need to pass only their beginnings**. When you call algorithms for multiple ranges, **make
sure that the second and additional ranges have at least as many elements as the first range**.  

```cpp
if (equal (coll1.begin(), coll1.end(), // first range
    coll2.begin())) {                  // second range
    ...
}
```

## Manipulating Algorithms  

Manipulating Algorithms是指会“移除或重排或修改”元素的算法  

### 移除元素  

```cpp
list<int> coll;

for (int i = 1; i <= 6; ++i) {
    coll.push_back(i);
    coll.push_front(i);
}
cout << "pre:  ";
copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
cout << endl;

remove(coll.begin(), coll.end(), 3);

cout << "post: ";
copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
cout << endl;
```

上面这段程序输出  

```md
pre:  6 5 4 3 2 1 1 2 3 4 5 6
post: 6 5 4 2 1 1 2 4 5 6 5 6
```

原因是数值为3的元素被后面的元素覆盖了，但是，remove()并没有改变集合中元素的数量，可以用下述代码删除数值为3的元素  

```cpp
coll.erase (remove(coll.begin(),coll.end(), 3), coll.end());
```

### 更改关联容器或无序容器  

更易型算法若用于关联式容器或无序容器，会出问题。（原因是关联式容器和无序容器的迭代器均被声明为指向常量的value或key）。如果要删除容器的某个指定元素，则应该使用容器的成员函数。每一种关联式容器或无序容器都提供了移除元素的成员函数，比如可以调用erase().  

```cpp
coll.erase(3);
```

### Algorithms versus Member Functions  

Even if you are able to use an algorithm, it might be a bad idea to do so. **A container might have member functions that provide much better performance**. Calling remove() for elements of a list is a good example of this. If you call remove() for elements of a list, the algorithm doesn’t know that it is operating on a list and thus does what it does for any container: reorder the elements by changing their values. To avoid bad performance, lists provide special member functions for all manipulating algorithms. You should always prefer them.  

## Container Elements  

The elements of STL containers must meet the following three fundamental requirements:  

1.**An element must be copyable or movable**. Thus, an element type implicitly or explicitly has to
provide a copy or move constructor. A generated copy should be equivalent to the source. This means that any test for equality returns that both are equal and that both source and copy behave the same.
2.**An element must be (move) assignable by the assignment operator**. Containers and algorithms use assignment operators to overwrite old elements with new elements.
3.**An element must be destroyable by a destructor**. Containers destroy their internal copies of elements when these elements are removed from the container. **Thus, the destructor must not be private**. Also, as usual in C++, a destructor must not throw; otherwise, all bets are off.  

These three operations are generated implicitly for any class. Thus, **a class meets the requirements automatically**, provided that no special versions of these operations are defined and no special members disable the sanity of those operations. **Elements might also have to meet the following requirements**:  

• **For some member functions of sequence containers, the default constructor must be available**. For example, it is possible to create a nonempty container or increase the number of elements with no hint of the values those new elements should have. These elements are created without any arguments by calling the default constructor of their type.  
• **For several operations, the test of equality with operator == must be defined and is especially needed when elements are searched**. For unordered containers, however, you can provide your own definition of equivalence if the elements do not support operator == .  
• **For associative containers, the operations of the sorting criterion must be provided by the elements**. By default, this is the operator <, which is called by the less<> function object.  
• **For unordered containers, a hash function and an equivalence criterion must be provided for the elements**.  

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 6  
