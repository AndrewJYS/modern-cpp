# 移动语义  

## 为什么需要移动语义  

右值引用是用来支持移动语义的。移动语义可以将资源（堆，系统对象等）从一个对象转到另一个对象，这样就避免了不必要的临时对象的创建、拷贝和销毁，从而大幅提高程序性能。下面例子中，不同编译器会有不同的结果，有些编译器并没有优化到最佳性能。为了保证优化到下例的最佳性能，应该使用移动语义。  

```c++
class MyString
{
public:
    MyString(char* tmp = "abc")
    {
        m_len = strlen(tmp);
        m_string = new char[m_len + 1];
        strcpy(m_string, tmp);

        cout << "含参构造函数，tmp = " << tmp << endl;
    }

    MyString(const MyString& tmp)
    {
        m_len = tmp.m_len;
        m_string = new char[m_len + 1];
        strcpy(m_string, tmp.m_string);

        cout << "拷贝构造函数，tmp = " << tmp.m_string << endl;
    }

    MyString& operator=(const MyString& tmp)
    {
        if (this == &tmp) //注意不能写成*this == tmp
        {
            return *this;
        }
        //先释放原来的内存
        m_len = 0;
        delete [] m_string;

        // 重新申请内容
        m_len = tmp.m_len;
        m_string = new char[this->m_len + 1];
        strcpy(m_string, tmp.m_string);

        cout << "赋值运算符重载，tmp = " << tmp.m_string << endl;

        return *this;
    }

    ~MyString()
    {
        cout << "析构函数: ";
        if (this != NULL)
        {
            delete [] m_string;
            m_string = NULL;
            m_len = 0;
            cout << "已操作delete" << endl;
        }
    }

private:
    int     m_len;
    char*   m_string;
};

MyString func()
{
    MyString tmp("mike");
    return tmp;
}

int main()
{
    MyString tmp = func();
    //含参构造函数，tmp = mike
    //析构函数: 已操作delete
    //但有些编译器可能不会优化，会有额外步骤，因此最好使用移动语义，保证最优

    return 0;
}
```

## 移动构造函数  

使用移动构造函数后，上述例子即使在最坏情况下，也不会额外申请空间  

```c++
class MyString
{
public:
......
    //移动构造函数
    //参数是非const的右值引用
    MyString(MyString && t) noexcept
    {
        m_string = t.m_string; //拷贝地址，没有重新申请内存
        m_len = t.m_len;
        t.m_string = NULL;  // 原指针置空
        cout << "移动构造函数" << endl;
    }
......

int main()
{
    MyString && tmp2 = func(); // 右值引用接收，引发“移动构造函数”

    //因此，在编译器不优化的情况下，函数的调用如下
    // 含参构造函数
    // 移动构造函数
    // 析构函数（不需要delete）
    // 析构函数（这是main函数结束后，需要delete）

    return 0;
}
```

## 移动赋值函数  

如果按照上述MyString类的代码，那么下面几行代码  

```c++
MyString func()
{
    MyString obj("mike");
    return obj;
}

int main()
{
    MyString tmp("abcd");
    tmp = func();
    return 0;
}
```

会调用多次函数（若编译器没有优化），分别为：  

```md
MyString tmp("abcd")调用含参构造函数
MyString obj("mike")调用含参构造函数
在return obj时调用移动构造函数，生成一个临时对象
func()调用完毕，obj释放，调用析构函数，无需delete
tmp = func()中，新的临时变量给tmp赋值，调用运算符重载函数
赋值完后，临时对象的生命周期结束，调用析构函数，需要delete
main函数结束，调用析构函数，tmp释放，需要delete
```

可以用移动赋值函数优化编译过程。  

```c++
// 移动赋值函数
// 无需重新申请堆区
MyString& operator=(MyString && t) noexcept
{
    if (this == &t)
    {
        return *this;
    }

    //先释放原来的内存
    m_len = 0;
    delete [] m_string;

    // 无需重新申请堆区
    m_string = t.m_string; //拷贝地址，没有重新申请内存
    m_len = t.m_len;
    t.m_string = NULL;  // 原指针置空

    cout << "移动赋值函数" << endl;

    return *this;
}
```

在编译器不优化的情况下，下述代码  

```c++
MyString func()
{
    MyString obj("mike");
    return obj;
}

int main()
{
    MyString tmp("abcd");
    tmp = func();
    return 0;
}
```

会调用这些函数：  

```md
MyString tmp("abcd")调用含参构造函数
MyString obj("mike")调用含参构造函数
在return obj时调用移动构造函数，生成一个临时对象
func()调用完毕，obj释放，调用析构函数，无需delete
tmp = func()中，调用移动赋值函数
赋值完后，调用析构函数，无需delete
main函数结束，调用析构函数，tmp释放，需要delete
```

可以看到，移动赋值函数对应的析构函数无需调用delete，因此提高了性能  

## std::move函数  

move()函数将左值转换成右值  

```c++
int a = 10; // a为左值
//int && b = a; // error
int && c = std::move(a);
cout << c << endl;
```

## noexcept 与 移动语义  

**实现移动构造函数以及移动赋值运算符时，使用了noexcept说明符**，下面简述原因  

考虑下述代码：  

```cpp
MyString tmp("a");
std::vector strs;
str.push_back(tmp);
str.push_back(tmp);
```

strs容器在定义时默认会申请1个元素的内存空间。当第1次执行str.push_back(tmp);时，对象tmp会被拷贝到容器第1个元素的位置。当第2次执行str.push_back(tmp);时，由于strs容器已没有多余的内存空间，因此它需要分配一块新的内存空间。在分配新的内存空间之后，strs容器会做2个操作：将对象tmp拷贝到容器第2个元素的位置，以及将之前的元素放到新的内存空间中容器第1个元素的位置。  

如果不加noexcept修饰移动构造函数，那么vector容器不会调用移动语义。原因是：没有使用noexcept说明符，也就没有保证移动构造函数不会抛出异常。因此，为了确保**强异常保证**，就只能使用拷贝构造函数了。  

**强异常保证**：即当我们调用一个函数时，如果发生了异常，那么应用程序的状态能够回滚到函数调用之前。容器的push_back函数是具备强异常保证的，也就是说，当push_back函数在执行操作的过程中，如果发生了异常，push_back函数需要确保应用程序的状态能够回滚到调用它之前。  

那么拷贝构造函数同样没有保证不会抛出异常，为什么就能用呢？这是因为拷贝构造函数执行之后，被拷贝对象的原始数据是不会丢失的。因此，即使发生异常需要回滚，那些已经被拷贝的对象仍然完整且有效。但移动语义就不同了，被移动对象的原始数据是会被清除的，因此如果发生异常，那些已经被移动的对象的数据就没有了，找不回来了，也就无法完成状态回滚了。  

## 完美转发  

完美转发，是指函数模板可以将自己的参数“完美”地转发给内部调用的其它函数。不仅能准确地转发参数的值，还能保证被转发参数的左、右值属性不变。用std::forward可以实现该机制  

```cpp
template<typename T>
void func(const T & )
{
    cout << "const T &" << endl;
}

template<typename T>
void func(T & )
{
    cout << "T &" << endl;
}

template<typename T>
void func(const T && )
{
    cout << "T &&" << endl;
}

template<typename T>
void forward_val(T && tmp)
{
    func( std::forward<T>(tmp) );
}

int main()
{
    int a = 0;
    const int &b = 1;

    forward_val(a);     // T &
    forward_val(b);     // const T &
    forward_val(111);   // T &&

    return 0;
}
```

## reference  

https://www.eet-china.com/mp/a158414.html  
