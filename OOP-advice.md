# 一些建议  

1.构造函数中的initialization list可以提高效率  

```cpp
class Test {
public:
    double a, b;
    Test(): a(0), b(0) {} //更高效
    //Test() { a = 0; b = 0; } //效率较低
}
```

2.当成员函数不改变成员变量时，在函数名末尾添加 const。

```cpp
void print() const {...}
```

如果不加，当用户声明const对象时调用non-const函数（不保证成员变量不变），会报错，比如下述情况会报错  

```cpp
const String str("hello");
str.print();  //String的成员函数print()没有加上const
```

3.成员函数尽量使用引用传递，而不是值传递。如果不想在函数内改变引用的值，那么加上const  

```cpp
void process(const vector<int>& arr);
```

返回值如果能用引用，也尽量使用，以提高效率（如果是在函数内临时生成的引用，要传出去，是不可以的，因为会在退出函数时销毁）  

4.重载赋值运算符时，首先判断赋值运算符两端对象不同  

```cpp
String& String::operator=(const Stirng& str) {
    if (this == &str)
        return *this;
    
    delete [] m_data; //m_data是成员变量  char* m_data，首先清空自身
    m_data= new char[ strlen(str.m_data) + 1 ];
    strcpy(m_data, str.m_data);
    return *this;
}
```

如果对象带有动态分配的内存，且左右对象相同，且不做第一步判断，那么在清空自身时，也会把赋值运算符右侧的自己清空，报错  

5.