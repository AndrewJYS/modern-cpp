# utilities  

## pair  

### 基本操作  

|Operation|Effect|examples|
:-:|:-:|:-:
| pair<T1,T2> p | Default constructor; creates a pair of values of types T1 and T2, initialized with their default constructors | std::pair<int, int> i_pair1; |
|pair<T1,T2> p(val1,val2) | Creates a pair of values of types T1 and T2, initialized with val1 and val2 | std::pair<int, int> i_pair2(2, 3); |
| pair<T1,T2> p(rv1,rv2) | Creates a pair of values of types T1 and T2, move initialized with rv1 and rv2 | std::string a = "hello"; </br> std::string b = "world"; </br> std::pair<std::string, std::string> s_pair1(std::move(a), std::move(b)); |
|pair<T1,T2> p(p2) | Copy constructor; creates p as copy of p2 | std::pair<std::string, std::string> s_pair2(s_pair1); </br> std::cout << s_pair2 << std::endl; // [hello, world] |
|pair<T1,T2> p(rv) | Move constructor; moves the contents of rv to p (implicit type conversions are possible) | std::pair<std::string, std::string> s_pair3(std::move(s_pair1)); </br> std::cout << s_pair1 << std::endl; // [, ] |
|p = p2 | Assigns the values of p2 to p (implicit type conversions are possible since C++11) | i_pair1 = i_pair2; |
|p = rv | Move assigns the values of rv to p (provided since C++11; implicit type conversions are possible) | std::pair<int, int> i_pair3; </br> i_pair3 = std::move(i_pair2);|
|p.first | Yields the first value inside the pair (direct member access) | |
p.second | Yields the second value inside the pair (direct member access) | |
|p1 == p2 | Returns whether p1 is equal to p2 (equivalent to p1.first==p2.first && p1.second==p2.second) | |
|p1.swap(p2) | Swaps the data of p1 and p2 (since C++11) | std::pair<int, int> i_pair4(1, 2); </br> std::pair<int, int> i_pair5(3, 4); </br> i_pair4.swap(i_pair5); </br> std::cout << i_pair5 << std::endl; // [1, 2]|
|swap(p1,p2) | Same (as global function) (since C++11) | swap(i_pair4, i_pair5); </br> std::cout << i_pair5 << std::endl; // [3, 4] |
|make_pair(val1,val2) | Returns a pair with types and values of val1 and val2 | std::cout << std::make_pair(15.7, '@') << std::endl; // [15.7, @] |

### 重载pair的<<运算符  

```c++
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& p)
{
    out << '[' << p.first << ", " << p.second << ']';
    return out;
}
```

### make_pair()  

With the new semantic of C++11, you can influence the type make_pair() yields by forcing either move or reference semantics. For move semantics, you simply use **std::move()** to declare that the passed argument is **no longer used**:  

```c++
std::string s1 {"str1"};
std::string s2 {"str2"};
auto p1 = std::make_pair(std::move(s1), std::move(s2)); // s1, s2 are no longer used
std::cout << p1 << std::endl; // [str1, str2]
p1.second = "345";
std::cout << s2.length() << std::endl; // 0
```

To force reference semantics, you have to use **ref()**, which forces a **reference** type,  

```c++
std::string s3 {"str3"};
std::string s4 {"str4"};
auto p2 = std::make_pair(std::ref(s3), std::ref(s4));
std::cout << p2 << std::endl; // [str3, str4]
p2.second = "123";
std::cout << s4 << std::endl; // 123
```

or **cref()**, which forces a **constant reference** type (both provided by \<functional\>;  

```c++
std::string s5 {"str5"};
std::string s6 {"str6"};
auto p3 = std::make_pair(std::cref(s5), std::cref(s6));
std::cout << p3 << std::endl; // [str5, str6]
//p4.second = "123"; // err
```

## smart pointers  

C++11中有unique_ptr, shared_ptr和weak_ptr等智能指针，定义在\<memory\>中。可以对动态资源进行管理，保证任何情况下，已构造的对象最终会销毁，即它的析构函数最后会被调用  

### std::shared_ptr  

#### basic operations of shared_ptr  

we need a semantics of “cleanup when the object is nowhere used anymore.” Class shared_ptr provides this semantics of shared ownership. Thus, multiple shared_ptrs are able to share, or **“own,” the same object**. The **last owner of the object is responsible for destroying** it and cleaning up all resources associated with it.

we use several examples to illustrate basic opeartions of std::shared_ptr, including initialization, modifying content, dereference, use_count() and release.  

Note that there are several ways to initialize and modify content of and release shared_ptr.  

**use_count()** yields the **current number of owners** an object referred to by shared pointers has.  

简而言之：shared_ptr允许多个该智能指针共享同一堆分配对象的内存，这通过引用计数(reference counting)实现，会记录有多少个shared_ptr共同指向一个对象，一旦最后一个这样的指针被销毁，也就是某个对象的引用计数变成0，这个对象会被自动删除  

第一组例子:  

```cpp
shared_ptr<int> sp1(new int(11));
shared_ptr<int> sp2 = sp1; // 拷贝构造函数
cout << *sp2 << endl; // 1
cout << sp2.use_count() << endl; //打印引用计数, 2
cout << sp1.use_count() << endl; //打印引用计数, 2

sp1.reset(); // 释放
cout << *sp2 << endl; // 11
// cout << *sp1 << endl; // error,sp1已经释放
cout << sp1.use_count() << endl; // 0，因为sp1释放了，所以它的引用计数为0
cout << sp2.use_count() << endl; // 1，因为sp1释放了，sp2的引用计数会减一
sp2.reset(); // 再次释放
```

第二组例子：  

```c++
//initialize
shared_ptr<string> pJohn1(new string{"john"});
shared_ptr<string> pJohn2 = pJohn1;  // copy constructor
shared_ptr<string> pAlen = make_shared<string>("alen");
shared_ptr<string> pBob;
pBob.reset(new string{"bob"});

//modify
(*pBob)[0] = 'B';
pAlen->replace(0, 1, "A"); //use member function of std::string

//dereference
cout << *pAlen << endl; //Alen
cout << *pBob << endl; //Bob

//use_count()
vector<shared_ptr<string>> names;
names.push_back(pAlen);
names.push_back(pAlen);
names.push_back(pAlen);
names.push_back(pAlen);
cout << pAlen.use_count() << endl;  // 5

//release
names[0] = nullptr;
cout << pAlen.use_count() << endl;  // 4
names.resize(3);
cout << pAlen.use_count() << endl;  // 3, names[0] = nullptr
names[1].reset();
cout << pAlen.use_count() << endl;  // 2
pAlen.reset();
cout << names[2].use_count() << endl;  // 1
cout << pAlen.use_count() << endl;  // 0
```

#### Defining a Deleter  

We can declare our own deleter  

```c++
shared_ptr<string> pNico(new string{"Nico"},
                        [](string* p) {
                        cout << "delete " << *p << endl;
                        delete p;
                        });
pNico = nullptr; // output: delete Nico
```

The **lambda function gets called when the last owner of a string gets destroyed**.  

### weak_ptr  

weak_ptr是为了配合shared_ptr而引入的一种智能指针。它可以从一个shared_ptr或另一个weak_ptr对象构造，它的构造和析构不会引起引用计数的增加或减少。没有重载*和->运算符，但是可以通过lock()获得一个可用的shared_ptr对象。  

```c++
shared_ptr<int> p1(new int(11));
shared_ptr<int> p2 = p1;
weak_ptr<int> wp1 = p1;
cout << p1.use_count() << " " << p2.use_count() << " " << wp1.use_count() << endl; // 2 2 2

// weak_ptr虽然不和堆区空间绑定，但可以通过lock函数获取shared_ptr<int>对象
shared_ptr<int> p3 = wp1.lock();
cout << p1.use_count() << " " << p2.use_count() << " " << p3.use_count() << " " << wp1.use_count() << endl; // 3 3 3 3

cout << *p1 << " " << *p2 << " " << *p3 << endl; // 11 11 11
// cout << *wp1 << endl; // error，没有重载*

p1.reset();
p2.reset();
p3.reset();
cout << p1.use_count() << " " << p2.use_count() << " " << p3.use_count() << endl; // 0 0 0

// 当堆区空间释放了，wp1.lock()返回为nullptr
shared_ptr<int> tmp = wp1.lock();
if (tmp == nullptr) cout << "堆区空间释放" << endl;
```

### unique_ptr  

unique_ptr持有对对象的独有权，同一时刻只能有一个unique_ptr指向给定对象（通过禁止拷贝语义、只有移动语义来实现）。  
unique_ptr的声明周期：从指针创建开始，直到离开作用域  

```c++
unique_ptr<int> up1(new int(11)); //创建智能指针对象
cout << *up1 << endl; //unique_ptr重载了operator*()
up1 = nullptr; // 也可以人为指定释放堆区空间,NULL和reset()也可以，如下
up1 = NULL;
up1.reset(); // 多次释放也没有问题


{
    unique_ptr<Test> up2(new Test); //会输出 ”析构函数“
    // 说明到作用域外，会自动销毁
}


unique_ptr<int> up3(new int(10));
// unique_ptr<int> up4 = up3; // error, forbid copy constructor
unique_ptr<int> up4 = std::move(up3); // 把up3的使用权转交给up4，up3不能被使用
cout << *up4 << endl; // 10
// cout << *up3 << endl; // error


// up4.reset()如果没有参数，作用是显式释放堆区内容
up4.reset(new int(22)); // 如果有参数，先释放原来堆区内容，重新给up1绑定一个新的堆区内容
cout << *up4 << endl; // 22


unique_ptr<int> up5(new int(15));
int* p = up5.release(); // 释放控制权，不释放堆区内存
cout << *p << endl; // 15
// cout << *up5 << endl;  // error
delete p;
```

## type-trait  

A **type trait provides a way to deal with the properties of a type**. It is a template, which at compile time **yields a specific type or value** based on one or more passed template arguments, which are usually types.  
Consider the following example:  

```cpp
template <typename T>
void foo(const T& val)
{
    if (std::is_pointer<T>::value) {
        std::cout << "foo() called for a pointer" << std::endl;
    }
    else {
        std::cout << "foo() called for a value" << std::endl;
    }
}
```

Here, the trait **std::is_pointer**, defined in \<type_traits\>, is used to **check whether type T is a pointer type**. In fact, **is_pointer<> yields either a type true_type or a type false_type**, for which **::value either yields true or false**. As a consequence, foo() will output  

```md
foo() called for a pointer
```

Another example for the usability of type traits is the need to process the “common type” of two or more types  

```cpp
template <typename T1, typename T2>
typename std::common_type<T1, T2>::type min_(const T1& val1, const T2& val2)
{
    return (val1 < val2) ? val1 : val2;
}
```

## swap()  

The function swap() is provided to swap the values of two objects. The general implementation of swap() is defined in \<utility\> as follows:  

```cpp
namespace std {
    template <typename T>
    inline void swap(T& a, T& b) ... {
        T tmp(std::move(a));
        a = std::move(b);
        b = std::move(tmp);
    }
}
```

Thus, internally, **the values are moved or move assigned**. By using this function, **you can have two arbitrary variables x and y swap** their values by calling std::swap(x,y);  

```c++
void test4()
{
    // swap()
    vector<int> v1;

    for (int i = 0; i < 5; i++)
    {
        v1.push_back(i);
    }

    vector<int> v2(10, 10);

    swap(v1, v2);
    for_each(v1.begin(), v1.end(), [](int val){cout << val << " ";});
    // 10 10 10 10 10 10 10 10 10 10
    cout << endl;
}
```

```cpp
class Person
{
public:
    Person():age(0), name("") {}
    Person(int age_, string name_): age(age_), name(name_) {}
    void toString() { cout << name << " " << age << endl; }

private:
    int age;
    string name;
};

int main()
{
    Person pa {14, "john"};
    Person pb {15, "ann"};
    swap(pa, pb);
    pa.toString(); // ann 15

    return 0;
}
```

The big advantage of using swap() is that it **enables you to provide special implementations for more complex types by using template specialization or function overloading**. These special implementations might **save time** by swapping internal members rather than by assigning the objects. You should always offer a specialization of swap() for your own types if doing so has performance advantages.  

## Definitions in \<cstring\>  

Table below shows the most important definitions of the \<cstring\> header file: the low-level functions to **set, copy, and move memory**.  

| Definition | Meaning |
:-:|:-:
|memchr (const void* ptr, int c, size_t len) |Finds character c in first len bytes of ptr|
|memcmp (const void\* ptr1, const void\* ptr2, size_t len) |Compares len bytes of ptr1 and ptr2
|memcpy (void\* toPtr, const void\* fromPtr, size_t len) |Copies len bytes of fromPtr to toPtr|
|memmove (void\* toPtr, const void\* fromPtr, size_t len) |Copies len bytes of fromPtr to toPtr (areas may overlap)|
|memset (void* ptr, int c, size_t len) |Assigns character c to first len bytes of ptr|  

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 5  
课程：https://www.bilibili.com/video/BV1QL4y1s7mC  
