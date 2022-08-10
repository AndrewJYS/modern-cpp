# Lecture2: thread Basics  

## join(), detach(), joinable()  

```c++
void my_func()
{
    cout << "my function begins" << endl;

    cout << "do 1" << endl;
    cout << "do 2" << endl;
    cout << "do 3" << endl;
    cout << "do 4" << endl;
    cout << "do 5" << endl;

    cout << "my function ends" << endl;
}

void test_my_func()
{
    //创建线程，线程的执行起点为my_func，my_thread线程开始执行
    thread my_thread(my_func); 

    //join():阻塞主线程并等待子线程执行完
    my_thread.join(); //阻塞主线程并等待子线程执行完

    //detach():子线程相当于被运行时库接管，当这个子线程执行完之后，由运行时库负责清理该线程的相关资源
    // 一旦调用了detach()，就不能再调用join()
    //my_thread.detach();

    //joinable():判断是否可以调用join()或detach()
    //true表示可以，false表示不行
    //在join()或者detach()使用后，joinable均为false
    if (my_thread.joinable())
    {
        cout << "joinable" << endl;
    }
    else
    {
        cout << "not joinable" << endl;
    }

    cout << "hello world" << endl;
    cout << "end 1" << endl;
    cout << "end 2" << endl;
    cout << "end 3" << endl;
}
```

如果用join()，最后输出如下：

```md
my function begins
do 1
do 2
do 3
do 4
do 5
my function ends
hello world
end 1
end 2
end 3
```

如果使用detach()，则my_func()函数的输出可能不完整  

## 使用函数对象作为thread的调用对象  

```c++
class Func1
{
public:
    void operator()()
    {
        cout << "Func1 begins" << endl;
        cout << "Func1 ends" << endl;
    }
};

void test_Func1()
{
    Func1 func;
    thread my_thread(func);
    my_thread.join();

    cout << "hello world" << endl;
}

/*输出
Func1 begins
Func1 ends
hello world
*/
```

注意，当函数对象拥有引用变量时，**使用detach()很危险**，如果主线程收回时，会销毁引用变量，而子线程还没有结束，那么子线程将在访问引用变量时出现不可预料的结果  

```c++
class Func2
{
public:
    int& m_i;
    Func2(int& i): m_i(i) {}

    void operator()()
    {
        for (int j = 0; j < 100; ++j)
        {
            cout << j << ": " << m_i << endl;
        }
    }
};

void test_Func2()
{
    int state = 10;
    Func2 func(state);
    thread my_thread(func);
    //my_thread.join();
    my_thread.detach(); //危险！state被主线程回收后，子线程会发生不可预料的结果

    cout << "hello world" << endl;
}
```

如果进一步考察，创建thread对象的机制，我们发现，创建thread时，会将Func3对象复制到子线程中，当主线程销毁时，销毁了外面的Func3对象，但是，子线程的Func3对象仍然存在，并且可以被访问。下述代码中，Func3 func 会调用无参构造函数；thread my_thread(func) 会调用拷贝构造函数，子线程和主线程结束后会分别调用析构函数  

```c++
class Func3
{
public:
    Func3()
    {
        cout << "无参构造函数" << endl;
    }

    Func3(const Func3& f)
    {
        cout << "拷贝构造函数" << endl;
    }

    ~Func3()
    {
        cout << "析构函数" << endl;
    }

    void operator()()
    {
        cout << "Func3 begins" << endl;
        cout << "Func3 ends" << endl;
    }
};

void test_Func3()
{
    Func3 func;
    thread my_thread(func); //会调用拷贝构造函数
    my_thread.join();
    //my_thread.detach();

    cout << "hello world" << endl;
}
```

## lambda表达式作为thread的传递对象  

```c++
void test_lambda()
{
    auto p = []{
        cout << "my lambda begins" << endl;
        cout << "my lambda ends" << endl;
    };

    thread my_thread(p);
    my_thread.join();

    cout << "hello world" << endl;
}

/*输出
my lambda begins
my lambda ends
hello world
*/
```
