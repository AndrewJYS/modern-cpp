# string  

## 概述  

Table below lists all operations that are provided for strings.  

|Operation |Effect|
:-:|:-:
|constructors |Create or copy a string|
|destructor |Destroys a string|
|=, assign() |Assign a new value|
|swap() |Swaps values between two strings|
|+=, append(), push_back() |Append characters|
|insert() |Inserts characters|
|erase(), pop_back() |Deletes characters (pop_back() since C++11)|
|clear() |Removes all characters (empties a string)|
|resize() |Changes the number of characters (deletes or appends characters at the end)|
|replace() |Replaces characters|
|+ |Concatenates strings|
|==, !=, <, <=, >, >=, compare() |Compare strings|
|empty() |Returns whether the string is empty|
|size(), length() |Return the number of characters|
|max_size() |Returns the maximum possible number of characters|
|capacity() |Returns the number of characters that can be held without reallocation|
|reserve() |Reserves memory for a certain number of characters|
|shrink_to_fit() |Shrinks the memory for the current number of characters (since C++11)|
|[ ], at() |Access a character|
|front(), back() |Access the first or last character (since C++11)|
|>>, getline() |Read the value from a stream|
|<< |Writes the value to a stream|
|stoi(), stol(), stoll()| Convert string to signed integral value (since C++11)|
|stoul(), stoull() |Convert string to unsigned integral value (since C++11)|
|stof(), stod(), stold() |Convert string to floating-point value (since C++11)|
|to_string(), to_wstring() |Convert integral/floating-point value to string (since C++11)|
|copy() |Copies or writes the contents to a character array|
|data(), c_str() |Returns the value as C-string or character array|
|substr() |Returns a certain substring|
|find functions |Search for a certain substring or character|
|begin(), end() |Provide normal iterator support|
|cbegin(), cend() |Provide constant iterator support (since C++11)|
|rbegin(), rend() |Provide reverse iterator support|
|crbegin(), crend() |Provide constant reverse iterator support (since C++11)|
|get_allocator() |Returns the allocator|

## 操作示例  

赋值和交换操作  

```cpp
string str1 = "abc";
string str2;
str1.assign("cde");
str2.assign("123");
cout << str1 << " " << str2 << endl;  // cde 123

swap(str1, str2);
cout << str1 << " " << str2 << endl;  // 123 cde
```

添加和插入操作  

```cpp
string str1 = "a";
str1 += "b";
str1.append("c");
str1.push_back('d');  // 注意push_back只能接收字符
cout << str1 << endl;  // abcd

// insert(下标，字符串)， insert(迭代器，字符，initializer list，区间)
str1.insert(0, "1");   
cout << str1 << endl;   // 1abcd
str1.insert(2, "222");
cout << str1 << endl;   // 1a222bcd
str1.insert(str1.begin(), '0'); //插入字符需要提供iterator
cout << str1 << endl;   // 01a222bcd

string str2 {"5555"};
str1.insert(str1.end(), str2.begin(), str2.end());
cout << str1 << endl;   // 01a222bcd5555
str1.insert(str1.begin(), 5, '6'); //插入字符需要提供iterator
cout << str1 << endl;   // 6666601a222bcd5555
```

删除操作  

```c++
string str1 = "1234567890";
str1.erase(1, 3);
cout << str1 << endl;  // 1567890

str1.erase(str1.begin(), str1.begin() + 2);
cout << str1 << endl;  // 67890

str1.erase(str1.begin());
cout << str1 << endl;  // 7890

str1.pop_back();
cout << str1 << endl;  // 789
```

修改字符  

```c++
string str1 = "abcdefghij";
char& a = str1[2];
char& b = str1[3];
a = '1';
b = '2';
cout << str1 << endl;  // ab12efghij

str1.replace(1, 5, "00"); //从下标1起始5个字符换成"00"
cout << str1 << endl;  // a00ghij

str1.replace(str1.begin(), str1.begin()+2, "1111");
cout << str1 << endl;  // 11110ghij
```

char* -> string  

```c++
char* str1 = "hello";
string str2(str1);
cout << str2 << endl;
```

string -> char*  
如果给void func(string s)传递char* 的变量，编译器会将char*变量隐式转换为string  
如果给void func(char* s)传递string的变量，编译器不会将string变量隐式转换为char*  

```c++
string str1 = "abcd";
const char* str2 = str1.c_str();
cout << str2 << endl;  // abcd

const char* str3 = str1.data();
cout << str3 << endl;  // abcd
```

从一个stream获取string  

```cpp
string str1;
getline(std::cin, str1);
cout << str1 << endl;

string str2;
getline(std::cin, str2, ':');
cout << str2 << endl;
/*
输入：aaaa
输出：aaaa
输入：aaaa:aaaa:bbbb
输出：aaaa
*/
```

与整数的转换  

```cpp
string str1 = "1234";
int i1 = stoi(str1);
cout << i1 << endl;

string str2 = to_string(i1);
cout << str2 << endl;
```

查询字符  

|String |Function Effect|
:-:|:-:
|find() |Finds the first occurrence of value|
|rfind() |Finds the last occurrence of value (reverse find)|
|find_first_of() |Finds the first character that is part of value|
|find_last_of() |Finds the last character that is part of value|
|find_first_not_of() |Finds the first character that is not part of value|
|find_last_not_of()| Finds the last character that is not part of value|

```cpp
std::string s("Hi Bill, I’m ill, so please pay the bill");
s.find("il") // returns 4 (first substring "il")
s.find("il",10) // returns 13 (first substring "il" starting from s[10])
s.rfind("il") // returns 37 (last substring "il")
s.find_first_of("il") // returns 1 (first char ’i’ or ’l’)
s.find_last_of("il") // returns 39 (last char ’i’ or ’l’)
s.find_first_not_of("il") // returns 0 (first char neither ’i’ nor ’l’)
s.find_last_not_of("il") // returns 36 (last char neither ’i’ nor ’l’)
s.find("hi") // returns npos
```

子字符串操作  

```cpp
std::string s("interchangeability");

s.substr() // returns a copy of s
s.substr(11) // returns string("ability")
s.substr(5,6) // returns string("change")
s.substr(s.find(’c’)) // returns string("changeability")

string email = "1234567890@qq.com";
int pos = email.find('@');
string qq = email.substr(0, pos);
cout << qq << endl;  // 1234567890
```

分割字符串  

```c++
string str =  "www.itcast.com.cn";
vector<string> v;
int start = 0;

while (1)
{
    int pos = str.find(".", start);

    if (-1 == pos)
    {
        v.push_back(str.substr(start));
        break;
    }

    v.push_back(str.substr(start, pos - start));
    start = pos + 1;
}

for (auto& str : v)
{
    cout << str << " ";
}

cout << endl;  // www itcast com cn
```

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 13  
https://www.bilibili.com/video/BV1hb411j7mu  
