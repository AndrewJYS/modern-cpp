# C++ 内存管理  

## new  

new有三种用法，分别是plain new，operator new，placement new  

plain new用于生成对象。会申请内存并调用构造函数  

```cpp
//Test是一个自定义类
Test* test = new Test(...);
```

operator new用于申请内存，作用与malloc()一样，实际上是函数调用。只会申请内存，不会调用构造函数  

```cpp
void* buff = operator new(sizeof(Test));
```

placement new用于调用构造函数初始化指定内存。只会调用构造函数，不会申请内存  

```cpp
void* testBuff = malloc(12);
Test* test = new (testBuff)Test();
```

完整示例如下：  

```cpp
class Test
{
public:
    Test() { printf("this is constructor\n"); }
    Test(int val) { printf("this is constructor, %d\n", val); }
    ~Test() { printf("this is destructor\n"); }
};

int main()
{
    Test* test1 = new Test(); //this is constructor
    delete test1; //this is destructor

    void* buff = operator new(sizeof(Test));

    void* testBuff = malloc(12);
    Test* test2 = new (testBuff)Test(12); //this is constructor, 12
    delete test2; //this is destructor

    return 0;
}
```

## 重载operator new  

事实上，plain new的内部会调用opeartor new，我们试着重载operator new  

### 重载 ::operator new（全局）

```cpp
void* myAlloc(size_t size)
{
    return malloc(size);
}

inline void* operator new(size_t size)
{
    cout << "this is my global operator new() \n";
    return myAlloc(size);
}

class Test { ...... };

int main()
{
    Test* test1 = new Test();
    //this is my global operator new()
    //this is constructor
    delete test1;

    return 0;
}
```

### 在类中重载 operator new  

相比重载全局的operator new，重载类中的会更有用  

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
    cout << "member operator new()" << endl;
    return p;
}

void Foo::operator delete(void* ptr, size_t size)
{
    cout << "member operator delete()" << endl;
    free(ptr);
}

void* Foo::operator new[](size_t size)
{
    Foo* p = (Foo*)malloc(size);
    cout << "member operator new[]()" << endl;
    return p;
}

void Foo::operator delete[](void* ptr, size_t size)
{
    cout << "member operator delete[]()" << endl;
    free(ptr);
}

int main()
{
    Foo* p = new Foo(7);
    delete p;

    Foo* pArray = new Foo[3];
    delete [] pArray;

    return 0;
}
```

输出如下：  

```shell
member operator new()
default ctor.this=0x8396c0 id=7
dtor.this=0x8396c0 id=7
member operator delete()

member operator new[]()
default ctor.this=0x8396c4 id=0
default ctor.this=0x8396e4 id=0
default ctor.this=0x839704 id=0
dtor.this=0x839704 id=0
dtor.this=0x8396e4 id=0
dtor.this=0x8396c4 id=0
member operator delete[]()

default ctor.this=0x8396c0 id=12
dtor.this=0x8396c0 id=12
```

## references  

[浅谈重载new操作符](https://blog.csdn.net/sinat_36817189/article/details/124599127)  
