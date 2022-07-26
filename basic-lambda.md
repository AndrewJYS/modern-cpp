# lambda  

## minimal lambda function  

The minimal lambda function has no parameters and simply does something. For example:  

```cpp
[] {
std::cout << "hello lambda" << std::endl;
}
```

You can call it directly:  

```cpp
[] {
std::cout << "hello lambda" << std::endl;
} (); // prints ‘‘hello lambda’’
```

or pass it to objects to get called:  

```cpp
auto l = [] {
std::cout << "hello lambda" << std::endl;
};
...
l(); // prints ‘‘hello lambda’’
```

## lambda introducer []  

[]，标识一个Lambda的开始，这一部分**必须存在**。函数对象参数是传递给编译器自动生成的函数对象类的构造函数的。函数对象参数只能使用到定义该Lambda表达式为止lamdba所在作用范围内定义过的局部变量，包括Lambda表达式所在类的成员变量。函数对象参数有以下几种形式：

空：代表不捕获Lambda表达式外的变量；  
&：代表以引用传递的方式捕获Lambda表达式外的变量；  
=：代表以值传递的方式捕获Lambda表达式外的变量，即以const引用的方式传值；
this：表示Lambda表达式可以使用Lambda表达式所在类的成员变量；  
a或=a：表示以值引用的方式传递变量a，即const int a,在函数体内不可改变a的值；但是可以对Lambda表达式使用mutable修饰符修饰，使得函数对象参数可以进行赋值，但是该函数对象参数不是被修改为引用传递方式；  
&a：表示以引用传递的方式传递变量a，在函数体内可以改变a的值；  
x，&y：x为值传递方式，y为引用传值方式；  
=，&x，&y：除x，y为引用传递方式以外，其他参数都为值传递方式进行传递；  
&，x，y：除x，y为值传递方式以外，其他参数都为引用传递方式进行传递；

注意：**全局变量的捕获是自动的，不需要写在[]内**  

```c++
int tmp = 1;

class Test
{
public:
    int i = 0;

    void func()
    {
        int a = 100;

        auto f1 = [=](){ cout << i << endl; };
        auto f2 = [&](){ cout << i << endl; };

        // this可以捕获成员变量和全局变量，但是不能捕获局部变量
        auto f3 = [this](){
            cout << i << endl;
            cout << tmp << endl;
            //cout << a << endl; // error
        };
    }
};

void lambda_basic()
{
    int a = 0, b = 0, c = 0;

    //空：代表不捕获Lambda表达式外的变量
    auto f1 = [](){};


    // a, b 以值传递，同时捕获tmp全局变量不需要显式写在[]内
    auto f2 = [a, b](){ cout << a << " " << b << " " << tmp << endl; };
    auto f3 = [a, b](int x, int y)
    {
        cout << a << " " << b << endl; // 0 0
        cout << x << " " << y << endl; // 10 11
    };
    f3(10, 11);


    // =：代表以值传递的方式捕获Lambda表达式外的变量，即以const引用的方式传值；
    auto f4 = [=]{
        cout << a << " " << b << endl;
        //a++; // error
    };
    auto f5 = [=]() mutable
    {
        cout << a << " " << b << endl;
        a++; // ok
    };


    // &：代表以引用传递的方式捕获Lambda表达式外的变量
    auto f6 = [&]{ cout << a << " " << b << endl; };

    // &，x，y：除x，y为值传递方式以外，其他参数都为引用传递方式进行传递；
    auto f7 = [&, a](){ cout << a << " " << b << endl; };

    // =，&x，&y：除x，y为引用传递方式以外，其他参数都为值传递方式进行传递；
    auto f8 = [=, &a]{ cout << a << " " << b << endl; };

}
```

## 按值传递和引用传递的区别  

按引用传递可以改变lambda外的变量  

```c++
int a = 10;
auto f1 = [=]() mutable
{
    a = 111;
    cout << a << endl;
};
f1(); // 111
cout << a << endl; // 10

int b = 10;
auto f2 = [&]()
{
    b = 111;
    cout << b << endl; // 111
};
f2();
cout << b << endl; // 111
```

## lambda表达式与仿函数  

仿函数是lambda表达式的一种实现方式，通过编译器都是把lambda表达式转化成一个仿函数对象。但是lambda表达式在编程时会更简单  

```c++
class MyFunctor
{
public:
    MyFunctor(int i): r(i) {}

    int operator()(int tmp)
    {
        return tmp + r;
    }

private:
    int r;
};

void lambda_functor()
{   
    int tmp = 10;

    // 仿函数写法（需要定义函数对象）
    MyFunctor obj(tmp);
    cout << obj(1) << endl; // 11

    // lambda
    auto f = [tmp](int t){return tmp + t;};
    cout << f(1) << endl; // 11
}
```

## lambda类型  

lambda表达式的类型在C++11中被称为闭包类型，每一个lambda表达式都会产生一个临时对象（右值），因此，lambda表达式不是函数指针.  

C++11标准允许将lambda表达式转化为函数指针，反之不行。但前提是lambda表达式没有捕获任何变量，且函数指针所示的函数原型，必须和lambda函数有着相同的调用方式

```c++
//下述例子表明lambda表达式可以转换成函数指针
function<void(int)> f1 = [](int a){ cout << a + 1 << endl; };
f1(9); // 10

function<int(int)> f2 = bind([](int a){return a + 1;}, std::placeholders::_1);
cout << f2(9) << endl; // 10

auto f3 = [](int x, int y) -> int { return x + y; }; // f3是一个函数指针
decltype(f3) f4 = f3;
cout << f4(2, 3) << endl; // 5

// 定义一个函数指针类型
typedef int (*PFUNC)(int, int);
PFUNC pf = f3;
cout << pf(10, 11) << endl; // 21
```

## lambda表达式应用举例  

```c++
vector<int> nums;
vector<int> largeNums;
int threshold = 5;

for (int i = 1; i <= 10; i++)
{
    nums.push_back(i);
}

for_each(nums.begin(), nums.end(),
            [&](int &tmp)
            {
                if (tmp > threshold)
                {
                    largeNums.push_back(tmp);
                }
            });

for_each(largeNums.begin(), largeNums.end(),
            [](int &tmp){ cout << tmp << " "; }); // 6 7 8 9 10
cout << endl;
```

## reference  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 3  
课程：C++标准11, 14; 侯捷  
课程：https://www.bilibili.com/video/BV1QL4y1s7mC  
