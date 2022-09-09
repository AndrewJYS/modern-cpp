# 函数对象（仿函数）  

## 函数对象概述  

1.函数对象（仿函数）是一个类，不是一个函数。函数对象重载了（）操作符使得它可以像函数一样调用  

```c++
class MyPrint1
{
public: 
    void operator()(int num)
    {
        cout << num << endl;
    }
};

void testMyPrint1()
{
    MyPrint mp;
    mp(10); // output: 10
}
```

2.仿函数可以维护自己的状态  

```c++
class MyPrint2
{
public:
    void operator()(int num)
    {
        cout << num << endl;
        m_count++;
    }
    int m_count = 0;
};

void testMyPrint2()
{
    MyPrint2 mp;
    mp(10);
    mp(10);
    mp(10);
    mp(10);

    cout << mp.m_count << endl; // 4
}
```

3.仿函数可以作为参数进行传递  

```c++
void run(MyPrint1 mp, int num)
{
    mp(num);
}

void test3()
{
    run(MyPrint1(), 10); //传递匿名对象
}
```

其他注意点：  
函数对象通常不定义构造函数和析构函数  
函数对象可内联编译，**性能比函数指针好**（用函数指针几乎不可能）  
模板函数对象使函数对具有通用性  

## for_each()和函数对象  

for_each()可以传回其接受的函数对象  

```cpp
using LL = long long;

class MeanValue
{
private:
    LL sum;
    LL num;

public:
    MeanValue(): num(0), sum(0) {}

    void operator()(int elem) {
        ++num;
        sum += elem;
    }

    double value() {
        return static_cast<double>(sum) / static_cast<double>(num);
    }
};

int main()
{
    vector<int> coll {1,2,3,4,5,6,7,8};
    MeanValue mv = for_each(coll.begin(), coll.end(), MeanValue());
    cout << "mean value: " << mv.value() << endl;

    return 0;
}
```

## 谓词  

谓词是指普通函数或重载的operator()返回值是bool类型的函数对象（仿函数）。如果operator接受一个参数，称作一元谓词，如果接受两个参数，称为二元谓词。谓词可作为一个判断式。  

注意：**碰到remove_if()函数（目前STL中，只有这个函数有问题，其他函数谓词没必要声明const），一定保证不能因为函数调用而改变谓词的状态，即如果谓词有成员变量，那么应当将operator()声明为const函数**（见C++标准库，第二版，485页）  

下面这个例子表明，仿函数可以协助算法完成不同的策略  

```c++
// 一元谓词的例子
#include <iostream>
#include <algorithm>
using namespace std;

class greaterThan20
{
public:
    bool operator()(int val)
    {
        return val > 20;
    }
};

void test4()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    // find_if()寻找v中第一个大于20的元素
    vector<int>::iterator pos = find_if(v.begin(), v.end(), greaterThan20());
    if (pos != v.end())
        cout << *pos << endl; // 30  
    else
        cout << "not found" << endl;
}
```

```c++
//二元谓词的例子 
class MyCmp
{
public:
    bool operator()(int v1, int v2)
    {
        return v1 > v2;
    }
};

void printVector(vector<int>& v)
{
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void test5()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(20);
    v.push_back(40);

    sort(v.begin(), v.end(), MyCmp());
    //[](){} 匿名函数 lambda
    for_each(v.begin(), v.end(), [](int val){cout << val << " ";}); // 40 30 20 10
    cout << endl;
}
```

## 预定义的函数对象  

STL内建了一些函数对象，分为算术类函数对象，关系运算类函数对象，逻辑运算类函数对象。这些函数对象所产生的对象，用法和一般函数完全相同。使用内建函数对象，要引入头文件functional.  

|Expression| Effect|
:-:|:-:
|negate\<type\>()          |- param|
|plus\<type\>()            |param1 + param2|
|minus\<type\>()           |param1 - param2|
|multiplies\<type\>()      |param1 * param2|
|divides\<type\>()         |param1 / param2|
|modulus\<type\>()         |param1 % param2|
|equal_to\<type\>()        |param1 == param2|
|not_equal_to\<type\>()    |param1 != param2|
|less\<type\>()            |param1 < param2|
|greater\<type\>()         |param1 > param2|
|less_equal\<type\>()      |param1 <= param2|
|greater_equal\<type\>()   |param1 >= param2|
|logical_not\<type\>()     |! param|
|logical_and\<type\>()     |param1 && param2|
|logical_or\<type\>()      |param1 || param2|
|bit_and\<type\>()         |param1 & param2|
|bit_or\<type\>()          |param1 | param2|
|bit_xor\<type\>()         |param1 ^ param2|  

```c++
negate<int> n;
cout << n(10) << endl; // -10

plus<int> p;
cout << p(1, 1) << endl;  // 2

divides<int> d1;
cout << d1(6, 3) << endl; // 2

divides<double> d2;
cout << d2(1, 3) << endl; //0.333333
```

```c++
void test7()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(20);
    v.push_back(40);

    sort(v.begin(), v.end(), greater<int>());
    for_each(v.begin(), v.end(), [](int val){cout << val << " ";}); // 40 30 20 10
    cout << endl;
    
    sort(v.begin(), v.end(), less<int>());
    for_each(v.begin(), v.end(), [](int val){cout << val << " ";}); // 10 20 30 40
    cout << endl;
}
```

## 函数对象适配器  

所谓函数对象适配器，是指能够将不同的函数对象（或是和某值或某寻常函数）结合起来的东西，它自身也是个函数对象。下表列出了自C++11开始，C++标准库提供的function adapter  

|Expression |Effect|
:-:|:-:
|bind(op,args...)| Binds args to op|
|mem_fn(op) |Calls op() as a member function for an object or |pointer to object|
|not1(op) |Unary negation: !op(param)|
|not2(op) |Binary negation: !op(param1,param2)|

### bind adapter  

```cpp
#include <functional>
using namespace std;
using namespace std::placeholders; //与functional头文件一起使用

auto plus10 = bind(plus<int>(), _1, 10);
cout << "7+10: " << plus10(7) << endl; //7+10: 17

auto plus10times2 = bind(multiplies<int>(), plus10, 2);
cout << "(7+10)*2: " << plus10times2(7) << endl; // (7+10)*2: 34

auto pow3 = bind(multiplies<int>(),
                 bind(multiplies<int>(), _1, _1),
                 _1);
cout << "7*7*7: " << pow3(7) << endl; // 7*7*7: 343

auto inversDivide = bind(divides<double>(), _2, _1);
cout << "7/49: " << inversDivide(49, 7) << endl; // 7/49: 0.142857
```

plus10, defined as  

```cpp
bind(plus<int>(), _1, 10);
```

represents a function object, which **internally calls plus<>** (i.e., operator +), with a **\_1 as first parameter**/operand and **10 as second parameter**/operand. The _1 represents the first argument passed to the expression as a whole. Thus, for any argument passed to this expression, **this function object yields the value of that argument +10**.  

if you pass this function object to an algorithm, the algorithm can apply it to every element the algorithms operates with. For example:  

```cpp
vector<int> coll {1,2,3,4,5,6,7};
transform(coll.begin(), coll.end(),
          coll.begin(),
          bind(plus<int>(), _1, 10));
for_each(coll.cbegin(), coll.cend(), 
         [](int val){ cout << val << " "; });
cout << endl; // 11 12 13 14 15 16 17
```

In the same way, you can define a binder that represents a sorting criterion. For example, to find the first element that is greater than 42, you bind greater<> with the passed argument as first and 42 as second operator:  

```cpp
// find first element >42
auto pos = std::find_if (coll.begin(),coll.end(),
                         std::bind(std::greater<int>(),_1,42));
```

### Calling Global Functions  

```cpp
void MyPrint3(int val, int start)
{
    cout << val + start << " ";
}

void test_bind3()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    cout << "Please enter start: " ;
    int num;
    cin >> num;
    for_each(v.cbegin(), v.cend(), bind(MyPrint3, _1, num));
    /*
    Please enter start: 100
    100 101 102 103 104 105 106 107 108 109
    */
}
```

### Calling Member Functions  

```cpp
class Person
{
public:
    Person(string name, int age):
        m_name(name), m_age(age)
    { }

    void print1() const {
        cout << "mf, name: " << m_name << "; age: " << m_age << endl;
    }

    void print2(const string& prefix) const {
        cout << prefix << m_name << "; age: " << m_age << endl;
    }

    void plusAge()
    {
        m_age++;
    }

    string m_name;
    int m_age;
};

void PrintPerson(Person& p)
{
    cout << "name: " << p.m_name << "; age: " << p.m_age << endl;
}

void test_bind4()
{
    vector<Person> v;
    Person p1("a", 15);
    Person p2("b", 25);
    Person p3("c", 20);
    Person p4("d", 10);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    for_each(v.begin(), v.end(), PrintPerson);
    /*
    name: a; age: 15
    name: b; age: 25
    name: c; age: 20
    name: d; age: 10
    */

    // 成员函数适配器
    for_each(v.begin(), v.end(), bind(&Person::print1, _1));
    /*
    mf, name: a; age: 15
    mf, name: b; age: 25
    mf, name: c; age: 20
    mf, name: d; age: 10
    */

    for_each(v.begin(), v.end(), bind(&Person::plusAge, _1));
    for_each(v.begin(), v.end(), bind(&Person::print2, _1, "Person: "));
    /*
    Person: a; age: 16
    Person: b; age: 26
    Person: c; age: 21
    Person: d; age: 11
    */
}
```

Here,  

```cpp
bind(&Person::print1, _1)  //一定要预留第一参数，该参数用于调用print1
```

defines a function object that calls param1.print1() for a passed Person. That is, because the first argument is a member function, the **next argument defines the object for which this member function gets called**.  

### mem_fn adapter  

For member functions, you can also use the **mem_fn() adapter**, whereby you can **skip the placeholder for the object the member function is called for**:  

```cpp
for_each(v.begin(), v.end(), mem_fn(&Person::print1));
/*
mf, name: a; age: 16
mf, name: b; age: 26
mf, name: c; age: 21
mf, name: d; age: 11
*/
```

## User-Defined Function Objects for Function Adapters  

```cpp
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <cmath>
using namespace std;
using namespace std::placeholders;

template <typename T1, typename T2>
struct mypow
{
    T1 operator() (T1 base, T2 exp) const
    {
        return std::pow(base, exp);
    }
};

void test()
{
    vector<int> coll {1,2,3,4,5,6,7,8,9};

    transform(coll.begin(), coll.end(),
              ostream_iterator<double>(cout, " "),
              bind(mypow<double, int>(), _1, 3));
    cout << endl;  // 1 8 27 64 125 216 343 512 729
}
```

## 旧版本的C++函数对象适配器（弃用）  

目前有这样的需求，将容器中的所有元素加上某个给定的数打印。这时不能仅用仿函数，而应使用函数对象适配器。  

使用方法如下：  
编写用于打印的仿函数  
继承binary_function<>, 尖括号<>中指明operator的参数类型和它的返回值  
重载的运算符后添加const  
用函数对象适配器bind2nd()将仿函数和的给定的增加值绑定起来  

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// 函数对象适配器
class MyPrint: public binary_function<int, int, void>
{ // 有两个参数，继承binary_function，尖括号<>中指明operator的参数类型和它的返回值
public:
    void operator()(int val, int start) const
    { // 加上const是因为父类中已经重载了operator，这里是重写父类函数，要与父类保持一致
        cout << val + start << " ";
    }
};

void test1()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    cout << "Please enter start: " ;
    int num;
    cin >> num;
    for_each(v.begin(), v.end(), bind2nd(MyPrint(), num)); // 函数对象适配器 bind2nd()
    /*
    Please enter start: 100
    100 101 102 103 104 105 106 107 108 109
    */
}
```

### 取反适配器  

一元取反：not1()  
二元取反：not2()  

```c++
class greaterThan5: public unary_function<int, bool>
{
public:
    bool operator()(int val) const
    {
        return val > 5;
    }
};

void test2()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    vector<int>::iterator pos = find_if(v.begin(), v.end(), not1(greaterThan5()));
    // 一元取反适配器 not1(), 继承unary_function<类型, 返回值类型>，加const
    if (pos != v.end())
        cout << "the number less than 5 is " << *pos << endl;
        // the number less than 5 is 0 （因为是从0开始搜索的，取第一个小于5的数就是0）
    else
        cout << "not found" << endl;

    // 上述写法等价于下面
    vector<int>::iterator pos2 = find_if(v.begin(), v.end(), not1(bind2nd(greater<int>(), 5)));
    // 一元取反适配器 not1(),继承unary_function<类型, 返回值类型>
    if (pos2 != v.end())
        cout << "the number less than 5 is " << *pos2 << endl;
        // the number less than 5 is 0 （因为是从0开始搜索的，取第一个小于5的数就是0）
    else
        cout << "not found" << endl;
}
```

### 函数指针适配器  

```c++
void MyPrint3(int val, int start)
{
    cout << val + start << " ";
}

void test3()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    cout << "Please enter start: " ;
    int num;
    cin >> num;
    // 函数指针适配器，将 函数指针 适配成 函数对象
    for_each(v.begin(), v.end(), bind2nd(ptr_fun(MyPrint3), num));
    /*
    Please enter start: 100
    100 101 102 103 104 105 106 107 108 109
    */
}
```

### 成员函数适配器  

```c++
class Person
{
public:
    Person(string name, int age)
    {
        this->m_name = name;
        this->m_age = age;
    }

    void showInfo()
    {
        cout << "member function----name: " << m_name << "; age: " << m_age << endl;
    }

    void plusAge()
    {
        m_age++;
    }

    string m_name;
    int m_age;
};

void PrintPerson(Person& p)
{
    cout << "name: " << p.m_name << "; age: " << p.m_age << endl;
}

void test4()
{
    vector<Person> v;
    Person p1("a", 15);
    Person p2("b", 25);
    Person p3("c", 20);
    Person p4("d", 10);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    for_each(v.begin(), v.end(), PrintPerson);
    /*
    name: a; age: 15
    name: b; age: 25
    name: c; age: 20
    name: d; age: 10
    */

    // 成员函数适配器
    for_each(v.begin(), v.end(), mem_fun_ref(&Person::showInfo));
    /*
    member function----name: a; age: 15
    member function----name: b; age: 25
    member function----name: c; age: 20
    member function----name: d; age: 10
    */

    for_each(v.begin(), v.end(), mem_fun_ref(&Person::plusAge));
    for_each(v.begin(), v.end(), mem_fun_ref(&Person::showInfo));
    /*
    member function----name: a; age: 16
    member function----name: b; age: 26
    member function----name: c; age: 21
    member function----name: d; age: 11
    */
}
```

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 10  
https://www.bilibili.com/video/BV1hb411j7mu  
