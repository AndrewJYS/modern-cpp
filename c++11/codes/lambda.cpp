#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

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


void test2()
{
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
}


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
{   int tmp = 10;

    MyFunctor obj(tmp);
    cout << obj(1) << endl; // 11

    // lambda
    auto f = [tmp](int t){return tmp + t;};
    cout << f(1) << endl; // 11
}


void lambda_type()
{
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
}


void lambda_vector()
{
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
}

int main()
{
//    lambda_basic();
//    test2();
//    lambda_functor();
    lambda_vector();

    return 0;
}
