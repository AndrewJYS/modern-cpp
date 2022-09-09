# 闭包  

闭包有很多种定义，一种说法是，闭包是带有上下文的函数。说白了，就是有状态的函数。一个函数，带上了一个状态，就变成了闭包了。意思是这个闭包有属于自己的变量，这些个变量的值是创建闭包的时候设置的，并在调用闭包的时候，可以访问这些变量。函数是代码，状态是一组变量，将代码和一组变量捆绑 (bind) ，就形成了闭包。内部包含 static 变量的函数，不是闭包，因为这个 static 变量不能捆绑。你不能捆绑不同的 static 变量，这个在编译的时候已经确定了。闭包的状态捆绑，必须发生在运行时。  

## 仿函数  

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

int main()
{
    MyFunctor mf(10);
    cout << mf(1) << endl; // 11

    return 0;
}
```

## std::bind()  

```c++
using namespace std;
using namespace std::placeholders;

void func(int x, int y)
{
    cout << x << " " << y << endl;
}

void test_bind()
{
     bind(func, 11, 22)(); // 11 22

     // std::placeholders::_1，函数调用时，被bind末尾()中第一个参数替换
     // std::placeholders::_2，函数调用时，被第二个参数替换
     bind(func, _1, _2)(11, 22); // 11 22
     bind(func, 11, _1)(2, 3, 4); // 11 2
     bind(func, _3, 11)(1, 3, 5); // 5 11
     bind(func, _2, _1)(11, 22); // 22 11
}
```

## std::function()  

```c++
// 普通函数
void func1()
{
    cout << __func__ << endl;
}

// 类中静态函数
class Test
{
public:
    static int test_func(int tmp)
    {
        cout << __func__ << "(" << tmp << ") -> ";
        return tmp;
    }
};

// 仿函数
class MyFunctor
{
public:
    int operator()(int tmp)
    {
        cout << __func__ << "(" << tmp << ") -> ";
        return tmp;
    }
};

void test_function()
{
    // 绑定普通函数
    function<void(void)> f1 = func1; // <void(void)> 括号内的void是指函数的参数类型，第一个void是函数返回值
    f1(); // func1

    // 绑定类中的静态函数
    function<int(int)> f2 = Test::test_func;
    cout << f2(10) << endl; // test_func(10) -> 10

    // 绑定仿函数
    MyFunctor obj;
    function<int(int)> f3 = obj;
    cout << f3(8) << endl; // operator()(8) -> 8
}
```

## references  

课程：https://www.bilibili.com/video/BV1QL4y1s7mC  
