# function templates  

Function templates are functions that are parameterized so that they represent a family of functions.  

## A First Look at Function Templates  

```c++
template<typename T>
T max(T a, T b)
{
    return a < b ? b : a;
}
```

You can use any type (fundamental type, class, and so on) as long as it **provides the operations that the template uses**. **In this case, type T has to support operator <** because a and b are compared using this operator.  

```c++
int i = 42;
std::cout << ::max(7, i) << std::endl; // 42

double f1 = 3.4;
double f2 = -6.7;
std::cout << "max(f1,f2): " << ::max(f1,f2) << '\n'; // max(f1,f2): 3.4

std::string s1 = "mathematics";
std::string s2 = "math";
std::cout << "max(s1,s2): " << ::max(s1,s2) << '\n'; // max(s1,s2): mathematics

/*notes: max() template is qualified with ::. This is to ensure that our max() template is found in the global namespace. There is also a std::max() template in the standard library, which under some circumstances may be called or may lead to ambiguity.*/
```

But, if we define a class 'MyString' and want to compare two 'MyString's, we should overload opeartor '<' (also, '<<')  

```c++
//\cpp-templates\basics\MyString.hpp
class MyString
{
public:
......
    friend bool operator<(const MyString& s1, const MyString& s2);
    friend std::ostream& operator<<(std::ostream& out, const MyString& s);

private:
    int     m_len;
    char*   m_string;
}

bool operator<(const MyString& s1, const MyString& s2)
{
    if (strcmp(s1.m_string, s2.m_string) < 0)
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& out, const MyString& s)
{
    out << s.m_string;
    return out;
}
```

```c++
MyString mystr1("abc");
MyString mystr2("bcd");
std::cout << "max(mystr1, mystr2): " << ::max(mystr1, mystr2) << '\n'; // max(mystr1, mystr2): bcd
```

## Template Argument Deduction  

Note that automatic type conversions are limited during type deduction:  
1.When declaring call parameters by **reference**, even trivial conversions do not apply to type deduction. Two arguments declared with the same template parameter T must **match exactly**.  
2.When declaring call parameters by **value**, only **trivial conversions that decay are supported**: Qualifications with const or volatile are ignored, references convert to the referenced type, and raw arrays or functions convert to the corresponding pointer type. For two arguments declared with the same template parameter T the decayed types must match.

```c++
max(4, 7.2); // ERROR: T can be deduced as int or double
std::string s;
foo("hello", s); // ERROR: T can be deduced as char const[6] or std::string
```

There are three ways to handle such errors:  
1.**Cast** the arguments so that they both match:  

```c++
max(static_cast<double>(4), 7.2); // OK
```

2.Specify (or qualify) explicitly the type of T to prevent the compiler from attempting type deduction:  

```c++
max<double>(4, 7.2); // OK
```

3.Specify that the parameters may have different types.  

## Multiple Template Parameters  

To ameliorate the code (especially the return type):  
1.Introduce a third template parameter for the return type.  
2.Let the compiler find out the return type (**recommended**).  
3.Declare the return type to be the “common type” of the two parameter types (**recommended**).  

```c++
//2.
template<typename T1, typename T2>
auto maxauto(T1 a, T2 b)
{
    return a < b ? b : a;
}
```

```c++
//3.
#include <type_traits>

template <typename T1, typename T2>
typename std::common_type<T1, T2>::type maxcommon(const T1& a, const T2& b)
{
    return b < a ? a : b;
}
```

## Default Template Arguments  

```c++
template <typename T1, typename T2,
          typename RT = typename std::decay_t<decltype(true? T1(): T2())>::type>
RT maxdefault1(const T1& a, const T2& b)
{
    return b < a ? a : b;
}

template <typename T1, typename T2,
          typename RT = typename std::decay<decltype(true? std::declval<T1>(): std::declval<T2>())>::type>
RT maxdefault2(const T1& a, const T2& b)
{
    return b < a ? a : b;
}

template <typename T1, typename T2,
          typename RT = typename std::common_type<T1, T2>::type>
RT maxdefault3(const T1& a, const T2& b)
{
    return b < a ? a : b;
}    int i = 42;
    //std::cout << "max(7,i): " << maxdefault1(7,i) << '\n'; //err, no matching function for call to 'maxdefault(int, int&)'
    std::cout << "max(7,i): " << maxdefault2(7,i) << '\n';
    std::cout << "max(7,i): " << maxdefault3(7,i) << '\n';
```

```c++
int i = 42;
//std::cout << "max(7,i): " << maxdefault1(7,i) << '\n'; //err, no matching function for call to 'maxdefault(int, int&)'
std::cout << "max(7,i): " << maxdefault2(7,i) << '\n';
std::cout << "max(7,i): " << maxdefault3(7,i) << '\n';
```

## references  

C++ templates, 2nd edition, chapter 1  
