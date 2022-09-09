#include <iostream>
#include <cstring>
using namespace std;

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

    //移动构造函数
    //参数是非const的右值引用
    MyString(MyString && t)
    {
        m_string = t.m_string; //拷贝地址，没有重新申请内存
        m_len = t.m_len;
        t.m_string = NULL;  // 原指针置空
        cout << "移动构造函数" << endl;
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

    // 移动赋值函数
    // 无需重新申请堆区
    MyString& operator=(MyString && t)
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

void test_move()
{
    int a = 10; // a为左值
    //int && b = a; // error
    int && c {std::move(a)};
    cout << c << endl; // 10
    cout << a << endl; // 10
}

int main()
{
    MyString tmp1 = func();
    //含参构造函数，tmp = mike
    //析构函数: 已操作delete

    //MyString && tmp2 = func();

    //MyString tmp("abcd");
    //tmp = func();

    //test_move();

    return 0;
}
