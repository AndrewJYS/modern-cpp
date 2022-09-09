# type & declaration  

## 类型推导  

### auto  

```c++
// 注意：auto在定义变量时，必须初始化
// 有些IDE不支持函数形参是auto变量
// auto变量不能作为自定义类型的成员变量。比如struct test{auto a = 10;};
// 不能定义auto数组。比如，auto b[2] = {1, 2};
// 模板实例化类型不能是auto类型。比如，vector<auto> b = {1};

auto a = 1; // int
auto b = 1.444; // double

vector<int> v(5, 10);
for (auto it = v.begin(); it != v.end(); it++)
    cout << *it << " ";
cout << endl; // 10 10 10 10 10
```

1.auto只能推断出类型，引用不是类型，所以auto无法推断出引用，要使用引用只能自己加引用符号  
2.声明为auto（不是auto&）的变量，忽视掉初始化表达式的**顶层const**。即对有const的普通类型(int 、double等)忽视const，对常量指针（顶层const）变为普通指针，对指向常量（底层const）的常量指针（顶层cosnt）变为指向常量的指针（底层const）。  
3.声明为auto&的变量，保持初始化表达式的顶层const或volatile 属性。  
4.若希望auto推导的是顶层const，加上const，即const auto。  

**关于顶层和底层const：**  
对于指针本身是一个常量，即指针的指向是一个常量，也就说不能改变指针的指向，称其为顶层const属性；对于指针指向的对象是一个常量，即指针指向的地址的值是一个常量，也就是说不能改变指针指向内存的值，称其为底层 const属性。在代码表现上是：  

```c++
int* cosnt p1 = &a;//p1是顶层const
cosnt int* p2 = &a;//p2是底层const
```

### decltype  

By using the new decltype keyword, you can let the compiler find out the type of an expression. This is the realization of the often requested typeof feature. However, the existing typeof implementations were inconsistent and incomplete, so C++11 introduced a new keyword.  

```c++
// decltype用来获取变量的类型
int i;
decltype(i) j = 0;
cout << typeid(j).name() << endl; // i(int)

// decltype(a + b)
float a;
double b;
decltype(a + b)c;
cout << typeid(c).name() << endl; // d(double)

// 迭代器
vector<int> v(5, 10);
decltype(v.begin()) k;
for (k = v.begin(); k != v.end(); k++)
    cout << *k << " ";
cout << endl; // 10 10 10 10 10

//还可以和lambda表达式与容器一起使用
class Person
{
public:
    string firstname() const { return m_firstname; }
    string lastname() const { return m_lastname; }
private:
    string m_firstname;
    string m_lastname;
};

auto cmp = [](const Person& p1, const Person& p2) {
    return p1.lastname() < p2.lastname() ||
        (p1.lastname() == p2.lastname() &&
        p1.firstname() < p2.firstname());
};
std::set<Person, decltype(cmp)> coll(cmp);
```

### 追踪返回类型  

```c++
// auto返回值与->(?)一起使用，表明该函数返回值可以根据->后面的要求自动推导

auto func1(int a, double b) -> int
{
    return a + b;
}

auto func2(int a, double b) -> double
{
    return a + b;
}

auto func3(int a, double b) -> decltype(a + b)
{
    return a + b;
}

// 在结合模板使用的时候，会有更大的作用
template<class T1, class T2>
auto mul(T1& t1, T2& t2) -> decltype(t1 * t2)
{
    return t1 * t2;
}

int main()
{
    auto a = 10;
    auto b = 11.1;
    cout << func1(a, b) << endl; // 21
    cout << func2(a, b) << endl; // 21.1
    cout << func3(a, b) << endl; // 21.1

    auto c = 10;
    auto d = 11.11;
    cout << mul(c, d) << endl; // 111.1

    return 0;
}
```

## uniform initialization and initializer list  

**C++11** introduced the concept of **uniform initialization**, which means that **for any initialization, you can use one common syntax**. This syntax uses **braces**, so the following is possible now:  

```cpp
int values[] { 1, 2, 3 };
std::vector<int> v { 2, 3, 5, 7, 11, 13, 17 };
std::vector<std::string> cities {"Berlin", "New York", "London", "Braunschweig", "Cairo", "Cologne" };
std::complex<double> c{4.0,3.0};

struct Test
{
    int a;
    double b;
    char c[10];
};
Test test = {1, 1.3, "name"};

class A
{
public:
    int data1 = 1;
    int data2{2};
    B data3{3};
    string data4{"4"};
};
```

An **initializer list forces so-called value initialization**, which means that even local variables of fundamental data types, which usually have an undefined initial value, are **initialized by zero** (or nullptr, if it is a pointer):  

```cpp
int i; // i has undefined value
int j{}; // j is initialized by 0
int* p; // p has undefined value
int* q{}; // q is initialized by nullptr
```

**narrowing initializations** — those that reduce precision or where the supplied value gets modified— are **not possible with braces**. For example:  

```cpp
int x3{5.0}; // ERROR: narrowing
int x4 = {5.3}; // ERROR: narrowing
char c2{99999}; // ERROR: narrowing (if 99999 doesn’t fit into a char)
std::vector<int> v2 { 1, 2.3, 4, 5.6 }; // ERROR: narrowing doubles to ints
```

When there are **constructors for both a specific number of arguments and an initializer list, the version with the initializer list is preferred**:  

```cpp
class P
{
public:
P(int,int);
P(std::initializer_list<int>);
};

P p(77,5); // calls P::P(int,int)
P q{77,5}; // calls P::P(initializer_list)
P r{77,5,42}; // calls P::P(initializer_list)
P s = {77,5}; // calls P::P(initializer_list)
```

**Without the constructor for the initializer list**, the constructor taking two ints would be called to initialize q and s, while **the initialization of r would be invalid**.  

### vector with initializer list  

```cpp
vector<int> v1 {1,2,3,4};
v1.insert(v1.begin() + 2, {10, 11});
for (auto i : v1)
    cout << i << " ";
cout << endl;  // 1 2 10 11 3 4
```

### minimum, maximum with initializer list  

```cpp
#include <algorithm>

cout << max({1, 3, 5, 2}) << endl; // 5
cout << min({1, 3, 5, 2}) << endl; // 1
cout << max({string("a"), string("b"), string("d"), string("c")}) << endl; // d
cout << min({string("a"), string("b"), string("d"), string("c")}) << endl; // a
```

## 左右值引用  

左值是可以放在赋值号左边，可以被赋值的值；左值必须要在内存中有实体；  
右值是在赋值号右边取出值赋给其他变量的值；右值可以在内存也可以在CPU寄存器。右值的例子包括表达式，临时对象等  
一个对象被用作右值时，使用的是它的内容(值)，被当作左值时，使用的是它的地址。

### 左值引用  

```c++
int& func1()
{
    static int tmp = 0;
    return tmp;
}

void testL()
{
    // 引用：给一个内存起一个别名，定义时必须初始化
    // 左值引用 (&)
    int a;
    int& b = a; // 给a起一个别名
    //int& c = 1; // error
    const int& d = a;
    const int& e = 1; // OK
    const int& f = func1();
}
```

### 右值引用  

右值引用可以解决非必要拷贝的问题，并且实现完美转发(perfect forwarding)（例子将会在移动语义和完美转发中给出）  

```c++
int func2()
{
    return 10;
}

void testR()
{
    // 右值引用 (&&)
    int && a = 10;
    int && b = func2();
    int i = 10;
    int j = 10;
    int && c = i + j;

    int k = 10;
    //int && d = k; //error.不能把一个左值赋值给一个右值引用
}
```

### 左右值引用函数的重载  

```c++
void test(int& tmp)
{
    cout << "left value is " << tmp << endl;
}

void test(int && tmp)
{
    cout << "right value is " << tmp << endl;
}

int main()
{
    int a = 10;
    test(a); // left value is 10
    test(111); // right value is 111

    return 0;
}
```

## Type Aliases  

Sometimes, we need a new name for a type. Possible reasons include:  
• The original name is too long, complicated, or ugly (in some programmer’s eyes).  
• A programming technique requires different types to have the same name in a context.  
• A specific type is mentioned in one place only to simplify maintenance.  
For example:  

```cpp
using Pchar = char∗; // pointer to character
using PF = int(∗)(double); // pointer to function taking a double and returning an int
```

The using keyword can also be used to introduce a template alias. For example:  

```cpp
template<typename T>
using Vector = std::vector<T, My_allocator<T>>;
```

We cannot apply type specifiers, such as unsigned, to an alias. For example:  

```cpp
using Char = char;
using Uchar = unsigned Char; // error
using Uchar = unsigned char; // OK
```

## reference  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Nicolai M. Josuttis, Chapter 3  
The C++ Programming Language, 4th Edition, Bjarne Stroustrup, Chapter 6  
课程：C++标准11, 14; 侯捷  
课程：https://www.bilibili.com/video/BV1QL4y1s7mC  
https://blog.csdn.net/weixin_43744293/article/details/117440727  
https://blog.csdn.net/weixin_43744293/article/details/117955427  
