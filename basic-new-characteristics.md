# new characteristics  

## range-based for  

C++11 introduces a new form of for loop, which iterates over all elements of a given range, array, or collection. The general
syntax is as follows:  

```cpp
for ( decl : coll ) {
    statement
}
```

where decl is the declaration of each element of the passed collection coll and for which the statements specified are called.  

declaring elem as a reference will accelerate speed, and you can change elements in the container  

```cpp
std::vector<double> vec;
...
for ( auto& elem : vec ) {
    elem *= 3;
}
```

to avoid calling the copy constructor and the destructor for each element, you should usually declare the current element to be a constant reference.  

```cpp
template <typename T>
void printElements (const T& coll)
{
    for (const auto& elem : coll) {
        std::cout << elem << std::endl;
    }
}
```

## noexcept  

C++11 provides the keyword noexcept. It can be used to specify that a function ***cannot throw*** — or is not prepared to throw. For example:  

```cpp
void foo () noexcept;  
```

declares that foo() won’t throw. If an exception is not handled locally inside foo() — thus, **if foo() throws — the program is terminated**, calling std::terminate(), which by default calls std::abort()  

```c++
// 下面两种写法都是该函数不抛出任何异常
void func1() throw() {   }
void func2() noexcept {   }
```

## nullptr  

```c++
// nullptr为了解决NULL的二义性
int a = NULL;
int* pa = NULL;

int *pb = nullptr;
// int b = nullptr; // 报错

if (pa == pb)
    cout << "equal" << endl; // equal
```

## 静态断言  

```c++
// assert 在运行时检查条件，如果条件为真，则继续执行，否则终止
bool cond = false;
assert(cond); // Assertion failed!

// 静态断言可以在编译时就判断条件，减小开销
// static_assert(常量表达式条件, "提示的字符串");
static_assert(sizeof(void*) == 4, "32位"); // 64位会编译时报错
```

## 常量表达式（constexpr)  

常量表达式允许一些计算发生在编译阶段，它将只做一次，而不是每次程序运行时都计算  
constexpr的限制：  
1.函数中只能有一个语句，且为return语句，函数必须有返回值  
2.但是函数中允许包含typedef, using, 静态断言  
3.return 语句中不能使用非常量表达式的函数，全局数据，只能是一个常量表达式  

```c++


constexpr int getConst1()
{
    return 4 + 104;
}

constexpr int getConst2()
{
    //constexpr int a = 1; // 报错
    return 6;
}

constexpr int getConst3()
{
    typedef int INT;
    return 4;
}

const int aa = 6;
constexpr int getConst4()
{
    // return a;  // 报错
}

int getINT()
{
    return 4;
}
constexpr int getConst5()
{
    //return getINT(); // 报错
}

int main()
{
    int a = getConst1();
    cout << a << endl;

    return 0;
}
```

## reference  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 3  
课程：C++标准11, 14; 侯捷  
课程：https://www.bilibili.com/video/BV1QL4y1s7mC  
