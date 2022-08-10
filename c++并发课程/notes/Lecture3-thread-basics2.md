# Lecture3: thread Basics  

## 陷阱  

假设我们有一个含参的函数，作为thread的传递对象，下面列举了使用detach()的两种常见问题  

```c++
// 问题1
void my_print1(const int& i, char* buf)
{
    cout << i << endl;
    //分析认为，i并不是var的引用，实际上是值传递；那么即使用了detach()，也不会因为主线程提前终止，而找不到i的值

    cout << buf << endl;
    //指针在detach()使用过程中，会有问题
}

void test_my_print1()
{
    int var = 1;
    char buffer[] = "test";
    thread my_thread(my_print1, var, buffer);
    my_thread.detach();
    cout << "hello world" << endl;
}
```

```c++
// 问题2
void my_print2(const int& i, const string& buf)
{
    cout << i << endl;

    cout << buf << endl;
    //理论上，string会以值传递的形式，交给子线程
    //但是，这里存在一个类型转换的问题，传入的实参是char buffer[], 要转成string
    //如果detach()的情况下，主线程已经结束，而仍然没有将char数组转成string，就会有问题
}

void test_my_print2()
{
    int var = 1;
    char buffer[] = "test";
    thread my_thread(my_print2, var, buffer);
    my_thread.detach();
    cout << "hello world" << endl;
}
```

解决方法如下：  

```c++
void my_print2(const int& i, const string& buf)
{
    // 同上
}

void test_my_print3()
{
    int var = 1;
    char buffer[] = "test";

    //针对上面的问题，改成string(buffer)后，即使使用detach()，程序也是安全的
    //在创建线程的同时构造临时对象传递是可行的
    //主线程运行到这一步时，会构造临时对象，然后主线程和子线程分开执行
    //也就是说，在主线程执行完毕之前，这个临时对象一定会被构造出来
    //即使主线程回收了，也不影响子线程继续使用这个对象
    thread my_thread(my_print2, var, string(buffer));
    my_thread.detach();
    cout << "hello world" << endl;
}
```

总结：  
1.若传递int这种简单类型参数，建议都是值传递，不要用引用，防止节外生枝  
2.如果传递类对象，避免隐式类型转换，全部都在创建线程这一行就构建出临时对象，然后在线程所要运行的函数的参数中用引用来接这个临时对象，否则系统仍然会多构造一次对象  
3.建议不使用detach()，除非detach在项目中有绝对优势  

## 线程id  

线程id可以用std::this_thread::get_id()获取  
可以利用线程id验证thread在接受参数时如果使用**隐式转换**或**构造临时对象**，底层的机制有何不同  
可以看到，如果是隐式转换，那么对传入参数的处理，均在子线程中完成，如果主线程提前回收，那么子线程就会发生不可预料的结果。如果是构造临时对象传入thread，就不会发生这种问题。主线程会拷贝一个对象给子线程  

```c++
class A
{
public:
    int m_i;

    A(int a): m_i(a)
    {
        cout << "含参构造函数: " << this << "; thread_id = " << std::this_thread::get_id() << endl;
    }

    A(const A& a)
    {
        m_i = a.m_i;
        cout << "拷贝构造函数: " << this << "; thread_id = " << std::this_thread::get_id() << endl;
    }

    ~A()
    {
        cout << "析构函数: " << this << "; thread_id = " << std::this_thread::get_id() << endl;
    }

};

void my_print(const A& a)
{
    cout << "子线程的参数地址是" << &a << "; thread_id = " << std::this_thread::get_id() << endl;
}

void test_id1()
{
    cout << "主线程id: " << std::this_thread::get_id() << endl;
    int state = 0;
    thread my_thread(my_print, state);
    my_thread.join();

    /* 输出：
    主线程id: 1
    含参构造函数: 0xf4fda0; thread_id = 2
    子线程的参数地址是0xf4fda0; thread_id = 2
    析构函数: 0xf4fda0; thread_id = 2
    */
}

void test_id2()
{
    cout << "主线程id: " << std::this_thread::get_id() << endl;
    int state = 0;
    thread my_thread(my_print, A(state));
    my_thread.join();

    /* 输出：
    主线程id: 1
    含参构造函数: 0x73fdd0; thread_id = 1
    拷贝构造函数: 0x73fd70; thread_id = 1
    拷贝构造函数: 0x1b2588; thread_id = 1
    析构函数: 0x73fd70; thread_id = 1 //对应第一个拷贝构造函数
    析构函数: 0x73fdd0; thread_id = 1 //对应含参构造函数
    子线程的参数地址是0x1b2588; thread_id = 2
    析构函数: 0x1b2588; thread_id = 2 //对应第二个拷贝构造函数
    */
    // 注意：由主线程拷贝的对象在地址0x1b2588，这个对象给了子线程
}
```

## 子线程改变所传递的对象  

从前面的例子可以看到，即使my_print()使用对象的引用来接受参数，但仍然会先拷贝一份交给子线程。这就带来一个问题，如果我们想要通过子线程修改这个对象，那么仅仅用引用'&'不能达到目的。这里要引入std::ref()  

```c++
class A
{
public:
    // 同上
};

void my_print(A& a)
{
    a.m_i = 199;
    cout << "子线程的参数地址是" << &a << "; thread_id = " << std::this_thread::get_id() << endl;
}

void test()
{
    cout << "主线程id: " << std::this_thread::get_id() << endl;
    A a(10);
    thread my_thread(my_print, std::ref(a));
    my_thread.join();
    cout << "a.m_i: " << a.m_i << endl;

    /*
    主线程id: 1
    含参构造函数: 0x73fdc0; thread_id = 1
    子线程的参数地址是0x73fdc0; thread_id = 2
    a.m_i: 199
    析构函数: 0x73fdc0; thread_id = 1
    */
}
```

## 使用智能指针作为thread参数  

```c++
void my_print(unique_ptr<int> a)
{
    cout << "子线程的参数地址是" << &a << "; thread_id = " << std::this_thread::get_id() << endl;
}

void test()
{
    cout << "主线程id: " << std::this_thread::get_id() << endl;
    unique_ptr<int> a(new int(100));
    thread my_thread(my_print, std::move(a));
    //cout << *a << endl; // error! 因为前面已经有std::move()
    my_thread.join();
    // 不能用detach()，因为如果主线程提前回收，子线程还在执行，子使用的参数a实际内存上是在主线程中的，那么子线程会使用被主线程回收的内存

    /*
    主线程id: 1
    子线程的参数地址是0xf3fda0; thread_id = 2
    */
}
```

## 使用成员函数指针作为thread参数  

```c++
class A
{
public:
    // 同上

    void thread_work(int num)
    {
        cout << "子线程执行: " << this << "; thread_id = " << std::this_thread::get_id() << endl;
    }
};

void test_class_member_function_pointer()
{
    A a(10);
    thread my_thread(&A::thread_work, a, 15); // 格式：类的成员函数指针，类对象，成员函数的参数
    my_thread.join();

    /*
    含参构造函数: 0x73fdc0; thread_id = 1
    拷贝构造函数: 0x73fd54; thread_id = 1
    拷贝构造函数: 0xb6258c; thread_id = 1
    析构函数: 0x73fd54; thread_id = 1
    子线程执行: 0xb6258c; thread_id = 2
    析构函数: 0xb6258c; thread_id = 2
    析构函数: 0x73fdc0; thread_id = 1
    */
}
```

也可以写成下面这种形式，主线程和子线程共用对象（此时一定不要用detach())  

```c++
void test_class_member_function_pointer2()
{
    A a(10);
    thread my_thread(&A::thread_work, &a, 15); // 类的成员函数指针，类对象，成员函数的参数
    my_thread.join();

    /*
    含参构造函数: 0x73fdc0; thread_id = 1
    子线程执行: 0x73fdc0; thread_id = 2
    析构函数: 0x73fdc0; thread_id = 1
    */
}
```
