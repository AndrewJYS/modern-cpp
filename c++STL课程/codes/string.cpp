#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    // 插入操作
    string s1 = "hello";
    s1.insert(1, "xxx");
    cout << s1 << endl;

    //删除操作
    s1.erase(1, 3);
    cout << s1 << endl;

    //char* -> string
    char* s2 = "hello";
    string s3(s2);
    cout << s3 << endl;

    //string -> char*;
    //如果给void func(string s)传递char* 的变量，编译器会将char* 变量隐式转换为string
    //如果给void func(char* s)传递string的变量，编译器不会将string变量隐式转换为char*
    const char* s4 = s3.c_str();
    cout << s4 << endl;

    // 修改字符
    string s5 = "abcdefg";
    char& a = s5[2];
    char& b = s5[3];
    a = '1';
    b = '2';
    cout << s5 << endl;

    // 截取子串
    string email = "1234567890@qq.com";
    int pos = email.find('@');
    string qq = email.substr(0, pos);
    cout << qq << endl;

    // 分割字符串
    string str =  "www.itcast.com.cn";
    vector<string> v;
    int start = 0;
    while (1)
    {
        int pos = str.find(".", start);

        if (pos == -1)
        {
            v.push_back(str.substr(start, str.length() + 1 - start));
            break;
        }

        v.push_back(str.substr(start, pos - start));
        start = pos + 1;
    }
    for (vector<string>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << (*it) << " ";
    }
    cout << endl;

    return 0;
}
