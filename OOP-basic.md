# class basics  

## 委托构造  

委托构造函数（Delegating Constructor）由 C++11 引入，是对 C++ 构造函数的改进，允许构造函数通过初始化列表调用同一个类的其他构造函数，目的是简化构造函数的书写，提高代码的可维护性，避免代码冗余膨胀。  

```c++
class Test
{
public:
    // 委托构造一定要通过初始化列表方式
    Test(): Test(1, 'a') {}
    Test(int x): Test(x, 'b') {}
    Test(char x): Test(11, x) {}

    int a;
    char b;

private:
    Test(int x, char y): a(x), b(y) {}
};

int main()
{
    Test t1;
    cout << t1.a << endl; // 1
    cout << t1.b << endl; // a

    Test t2(10);
    cout << t2.a << endl; // 10
    cout << t2.b << endl; // b

    Test t3('c');
    cout << t3.a << endl; // 11
    cout << t3.b << endl; // c

    return 0;
}
```

## new and delete  

### 一般情况  

假设我们有String类  

```cpp
String* ps = new String("Hello");
```

对于上述代码，编译器会执行下述步骤  

```cpp
String* ps;

void* mem = operator new(sizeof(String));
ps = static_cast<String*>(mem);
ps->String::String("Hello");
```

其中，operator new()内部会调用malloc()  

```cpp
delete ps;
```

对于上述代码，编译器会执行下述操作  

```cpp
String::~String(ps); //本来析构函数没有参数，这里会自动补全
operator delete(ps); //内部调用free(ps)
```

### 对象数组  

我们已经知道，new的内部会执行operator new操作，下面的例子中，我们重载了operator new，可以更清楚的看到，对象数组生成和销毁时的内存管理情况。  

如果生成一个对象指针并初始化，那么会先进行operator new()操作，然后调用构造函数。销毁这个对象指针时，先调用对象的析构函数，然后用operator delete()销毁内存。  

如果生成一个对象数组，那么首先会调用operator new\[\]()，分配足够的空间，然后根据数组大小n，调用n次构造函数。当销毁数组时，会调用n次析构函数，最后再调用operator delete\[\]()。  

```cpp
#include <iostream>
#include <string>
using namespace std;

class Foo
{
public:
    int m_id;
    long m_data;
    string m_str;

public:
    Foo():m_id(0) { cout << "default ctor.this=" << this << " id=" << m_id << endl; }
    Foo(int i):m_id(i) { cout << "default ctor.this=" << this << " id=" << m_id << endl; }

    ~Foo() {cout << "dtor.this=" << this << " id=" << m_id << endl; }

    static void* operator new(size_t size);
    static void* operator new[](size_t size);
    static void operator delete(void* ptr, size_t size);
    static void operator delete[](void* ptr, size_t size);
};

void* Foo::operator new(size_t size)
{
    Foo* p = (Foo*)malloc(size);
    cout << "member operator new(); allocate size: " << size << endl;
    return p;
}

void Foo::operator delete(void* ptr, size_t size)
{
    cout << "member operator delete(), release size: " << size << endl;
    free(ptr);
}

void* Foo::operator new[](size_t size)
{
    Foo* p = (Foo*)malloc(size);
    cout << "member operator new[](); allocate size: " << size << endl;
    return p;
}

void Foo::operator delete[](void* ptr, size_t size)
{
    cout << "member operator delete[](), release size: " << size << endl;
    free(ptr);
}

int main()
{
    Foo* p = new Foo(7);
    delete p;

    Foo* pArray = new Foo[3];
    delete [] pArray;

    Foo* g_p = ::new Foo(12);
    ::delete g_p;

    return 0;
}
```

输出如下：  

```md
member operator new(); allocate size: 32
default ctor.this=0x7496c0 id=7
dtor.this=0x7496c0 id=7
member operator delete(), release size: 32

member operator new[](); allocate size: 100
default ctor.this=0x7496c4 id=0
default ctor.this=0x7496e4 id=0
default ctor.this=0x749704 id=0
dtor.this=0x749704 id=0
dtor.this=0x7496e4 id=0
dtor.this=0x7496c4 id=0
member operator delete[](), release size: 100

default ctor.this=0x7496c0 id=12
dtor.this=0x7496c0 id=12
```

如果改成  

```cpp
Foo* pArray = new Foo[3];
delete pArray;
```

则会输出  

```md
member operator new[](); allocate size: 100
default ctor.this=0xef96c4 id=0
default ctor.this=0xef96e4 id=0
default ctor.this=0xef9704 id=0
dtor.this=0xef96c4 id=0
member operator delete(), release size: 32
```

只会调用一次析构函数，因此**针对动态分配内存的数组，在销毁时要用delete []**.  

## 类型转换  

### non-explicit  

下面的代码Fraction fp = f + 4;运行时，编译器会先检查是否定义了+操作，发现存在定义，但是类型并不匹配（一个是整数4，而参数是Fraction类型的对象），于是考虑类型转换，通过构造函数得到了值为(m_numerator = 4, m_denominator = 1)的Fraction对象，于是再用+操作进行运算得出结果(4.4)  

```cpp
#include <iostream>
using namespace std;

class Fraction
{
public:
    Fraction(int num, int den = 1)
        : m_numerator(num), m_denominator(den)
    { cout << "use ctor: " << num << "/" << den << endl; }

    Fraction operator+(const Fraction& f) {
        return Fraction(m_numerator * f.m_denominator + m_denominator * f.m_numerator, m_denominator * f.m_denominator);
    }

    void print() {
        cout << (double)m_numerator / m_denominator << endl;
    }

private:
    int m_numerator;
    int m_denominator;
};

int main()
{
    Fraction f(2, 5);
    Fraction fp = f + 4;
    fp.print();

    return 0;
}
```

```md
use ctor: 2/5
use ctor: 4/1
use ctor: 22/5
4.4
```

但是，如果增加一个operator double()转换函数，编译器就会发现有两条路线（另一条是通过opreator double()转换函数将Fraction类型转为double），会报二义性错误  

```cpp
Fraction(int num, int den = 1)
    : m_numerator(num), m_denominator(den) { cout << "use ctor" << endl; }

Fraction operator+(const Fraction& f) {
    return Fraction(m_numerator * f.m_denominator + m_denominator * f.m_numerator, m_denominator * f.m_denominator);
}

operator double() {
    cout << "use double()" << endl;
    return (double)m_numerator / m_denominator;
}
```

### explicit  

explicit一般用在构造函数上，禁止隐式转换。这时候，explicit会把上面提到的两条路都堵死，于是报错  

```cpp
explicit Fraction(int num, int den = 1)
    : m_numerator(num), m_denominator(den) { cout << "use ctor" << endl; }

Fraction operator+(const Fraction& f) {
    return Fraction(m_numerator * f.m_denominator + m_denominator * f.m_numerator, m_denominator * f.m_denominator);
}

operator double() {
    cout << "use double()" << endl;
    return (double)m_numerator / m_denominator;
}
```

## override & final  

### override

```cpp
class C1
{
public:
    // 这是第一个虚函数，没有重写，不能用override修饰
    virtual void run(int a) = 0;
};

class C2: public C1
{
public:
    // 在重写虚函数的地方，加上override，要求重写的虚函数和基类一模一样
    void run(int a) override {}
    //void run() override {} // 报错
    //int run() override {return 1;} // 报错
};
```

### final  

```c++
// final会阻止类的进一步派生，虚函数的进一步重写

class A1 final
{
    int a;
};

// class A2: public A1; //无法继承，报错

class B1
{
public:
    virtual void run() final;
};

class B2: public B1
{
    // void run() {} // 无法重写，报错
};
```

## =delete, =default  

如果自行定义了一个构造函数A(...){...}，那么编译器就不会再给你一个默认构造函数A(){}。如果给A()强制加上=default，就可以重新获取并使用A(){}。而且其效率比用户自己声明的A(){}高。同理，也可以修饰其他函数，使编译器自动提供对应函数的默认版本。但是，**=default只能修饰类中默认提供的函数：无参构造函数，拷贝构造函数，赋值运算符重载，析构函数**等  

```cpp
class A
{
public:
    A() =default;
    A(int i): m_i(i){}

    int m_i;
};

A a; // ok
```

=delete 可以禁用函数  

```cpp
class B
{
public:
    B() { cout << "无参构造函数" << endl; }
    B(const B&) { cout << "拷贝构造函数" << endl; }
    B& operator=(const B& ) {cout << "赋值运算符重载函数" << endl; return *this; }
};

class C
{
public:
    // =delete 可以禁用函数
    C() { cout << "无参构造函数" << endl; }
    C(const C&)=delete; // 用=delete修饰，此函数被禁用
    C& operator=(const C& )=delete;

    void print(const C& c)=delete;

    // =delete还可以禁用运算符
    void* operator new(size_t)=delete;
    void* operator new[](size_t)=delete;
};

int main()
{
    B obj1;             //ok
    B obj2(obj1);       //ok
    obj2 = obj1;        //ok

    C obj3;
    // C obj4(obj3);        // 报错，拷贝构造函数被禁用
    //C* p = new C;         // 报错，new运算符被禁用
    //C* parr = new C[10];  // 报错，new[]运算符被禁用
    //obj3.print(obj3);     //报错
    
    return 0;
}
```

## reference  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 3  
课程：C++标准11, 14; 侯捷  
课程：https://www.bilibili.com/video/BV1QL4y1s7mC  
