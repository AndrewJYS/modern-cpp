# complex & numeric functions  

## 复数概述

The class complex<> is declared in the header file \<complex\>:  

```cpp
#include <complex>
```

In \<complex\>, the class complex<> is defined as follows:  

```cpp
namespace std {
    template <typename T>
    class complex;
}
```

## 复数的基本操作  

### 创建，复制和赋值  

|Expression |Effect|
:-:|:-:
|complex c |Creates a complex number with 0 as the real part and 0 as the imaginary part (0 + 0i)|
|complex c(1.3) |Creates a complex number with 1.3 as the real part and 0 as the imaginary part (1.3 + 0i)|
|complex c(1.3,4.2) |Creates a complex number with 1.3 as the real part and 4.2 as the imaginary part (1.3 + 4.2i)|
|complex c1(c2) |Creates c1 as a copy of c2|
|polar(4.2) |Creates a temporary complex number from polar coordinates (4.2 as magnitude rho and 0 as phase angle theta)|
|polar(4.2,0.75) |Creates a temporary complex number from polar coordinates (4.2 as magnitude rho and 0.75 as phase angle theta)|
|conj(c) |Creates a temporary complex number that is the conjugated complex number of c (the complex number with the negated imaginary part)|
|proj(c) |Creates a temporary complex number from the projection of c onto the Riemann sphere (since C++11)|
|c1 = c2 |Assigns the values of c2 to c1|
|c1 += c2 |Adds the value of c2 to c1|
|c1 -= c2 |Subtracts the value of c2 from c1|
|c1 *= c2 |Multiplies the value of c2 by c1|
|c1 /= c2 |Divides the value of c2 into c1|

### 数值访问  

|Expression |Effect|
:-:|:-:
|real(c) |Returns the value of the real part (as a global function)|
|c.real() |Returns the value of the real part (as a member function)|
|c.real(1.7) |Assigns 1.7 as new real part (since C++11)|
|imag(c) |Returns the value of the imaginary part (as a global function)|
|c.imag() |Returns the value of the imaginary part (as a member function)|
|c.imag(1.7) |Assigns 1.7 as new imaginary part (since C++11)|
|abs(c) |Returns the absolute value of c|
|norm(c) |Returns the squared absolute value of c|
|arg(c) |Returns the angle of the polar representation of c (ϕ) (equivalent to atan2(c.imag(),c.real()) as phase angle)|

### 比较  

|Expression| Effect|
:-:|:-:
|c1 == c2 |Returns whether c1 is equal to c2 (c1.real()==c2.real() && c1.imag()==c2.imag())|
|c == 1.7 |Returns whether c is equal to 1.7 (c.real()==1.7 && c.imag()==0.0)|
|1.7 == c |Returns whether c is equal to 1.7 (c.real()==1.7 && c.imag()==0.0)|
|c1 != c2 |Returns whether c1 differs from c2 (c1.real()!=c2.real() || c1.imag()!=c2.imag())|
|c != 1.7 |Returns whether c differs from 1.7 (c.real()!=1.7 || c.imag()!=0.0)|
|1.7 != c |Returns whether c differs from 1.7 (c.real()!=1.7 || c.imag()!=0.0)|

### 算术运算  

|Expression| Effect|
:-:|:-:
|c1 + c2 |Returns the sum of c1 and c2|
|c + 1.7 |Returns the sum of c and 1.7|
|1.7 + c |Returns the sum of 1.7 and c|
|c1 - c2 |Returns the difference between c1 and c2|
|c - 1.7 |Returns the difference between c and 1.7|
|1.7 - c |Returns the difference between 1.7 and c|
|c1 \* c2 |Returns the product of c1 and c2|
|c \* 1.7 |Returns the product of c and 1.7|
|1.7 \* c |Returns the product of 1.7 and c|
|c1 / c2 |Returns the quotient of c1 and c2|
|c / 1.7 |Returns the quotient of c and 1.7|
|1.7 / c |Returns the quotient of 1.7 and c|
|- c |Returns the negated value of c|
|+ c |Returns c|
|c1 += c2 |Equivalent to c1 = c1 + c2|
|c1 -= c2 |Equivalent to c1 = c1 - c2|
|c1 \*= c2 |Equivalent to c1 = c1 * c2|
|c1 /= c2 |Equivalent to c1 = c1 / c2|

## 复数的操作示例  

leetcode537 复数乘法  

```md
复数 可以用字符串表示，遵循 "实部+虚部i" 的形式，并满足下述条件：

实部 是一个整数，取值范围是 [-100, 100]
虚部 也是一个整数，取值范围是 [-100, 100]
i^2 == -1
给你两个字符串表示的复数 num1 和 num2 ，请你遵循复数表示形式，返回表示它们乘积的字符串。
```

```cpp
string complexNumberMultiply(string num1, string num2) {
    int a1, b1, a2, b2;
    sscanf(num1.c_str(), "%d+%di", &a1, &b1);
    sscanf(num2.c_str(), "%d+%di", &a2, &b2);

    complex<int> c1(a1, b1);
    complex<int> c2(a2, b2);
    complex<int> res = c1 * c2;
    return to_string(res.real()) + '+' + to_string(res.imag()) + 'i';
}
```

## 全局数值函数  

|Function| Effect|
:-:|:-:
|\<cmath\>||
|pow()| Power function|
|sqrt() |Square root|
|ceil() |Floating-point value rounded up to the next integral value|
|floor() |Floating-point value rounded down to the next integral value|
|fabs() |Absolute value of a floating-point value|
|\<cstdlib\>||
|abs() |Absolute value of an int value|
|labs() |Absolute value of a long|
|llabs() |Absolute value of a long long (since C++11)|
|srand()| Random-value generator (seed new sequence)|
|rand() |Random-value generator (next number of sequence)|

```cpp
cout << fabs(-4.5) << endl;     // 4.5
cout << abs(-9.6) << endl;      // 9.6
cout << labs(-4.6) << endl;     // 4，截断
cout << llabs(-9.5) << endl;    // 9，截断
```

```cpp
#include <ctime>

srand((unsigned)time(0));
int a = rand()% 10 + 1;
cout << a << endl;
```

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 17  
