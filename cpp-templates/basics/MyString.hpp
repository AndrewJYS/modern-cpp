#ifndef MYSTRING_HPP_INCLUDED
#define MYSTRING_HPP_INCLUDED

#include <cstring>
#include <iostream>

class MyString
{
public:
    MyString();
    MyString(char* tmp);
    MyString(const MyString& tmp);
    MyString(MyString && t);
    MyString& operator=(const MyString& tmp);
    MyString& operator=(MyString && t);
    ~MyString();

    friend bool operator<(const MyString& s1, const MyString& s2);
    friend bool operator>(const MyString& s1, const MyString& s2);
    friend std::ostream& operator<<(std::ostream& out, const MyString& s);

private:
    int     m_len;
    char*   m_string;
};


MyString::MyString()
{
    m_string = "";
    m_len = 0;
}

MyString::MyString(char* tmp)
{ // 含参构造函数
    m_len = strlen(tmp);
    m_string = new char[m_len + 1];
    strcpy(m_string, tmp);
}

MyString::MyString(const MyString& tmp)
{ // 拷贝构造函数
    m_len = tmp.m_len;
    m_string = new char[m_len + 1];
    strcpy(m_string, tmp.m_string);
}

MyString::MyString(MyString && t)
{ //移动构造函数，参数是非const的右值引用
    m_string = t.m_string; //拷贝地址，没有重新申请内存
    m_len = t.m_len;
    t.m_string = NULL;  // 原指针置空
}

MyString& MyString::operator=(const MyString& tmp)
{ // 赋值运算符重载
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

    return *this;
}


MyString& MyString::operator=(MyString && t)
{ // 移动赋值函数，无需重新申请堆区
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

    return *this;
}

MyString::~MyString()
{
    if (this != NULL)
    {
        delete [] m_string;
        m_string = NULL;
        m_len = 0;
    }
}

bool operator<(const MyString& s1, const MyString& s2)
{
    if (strcmp(s1.m_string, s2.m_string) < 0)
        return true;
    return false;
}

bool operator>(const MyString& s1, const MyString& s2)
{
    if (strcmp(s1.m_string, s2.m_string) > 0)
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& out, const MyString& s)
{
    out << s.m_string;
    return out;
}

#endif // MYSTRING_HPP_INCLUDED
