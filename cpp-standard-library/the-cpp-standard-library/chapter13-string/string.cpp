#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <functional>
using namespace std;
using namespace std::placeholders;

void test_assign_swap()
{
    string str1 = "abc";
    string str2;
    str1.assign("cde");
    str2.assign("123");
    cout << str1 << " " << str2 << endl;  // cde 123

    swap(str1, str2);
    cout << str1 << " " << str2 << endl;  // 123 cde
}

void test_append_insert()
{
    string str1 = "a";
    str1 += "b";
    str1.append("c");
    str1.push_back('d');  // 注意push_back只能接收字符
    cout << str1 << endl;  // abcd

    str1.insert(0, "1");
    cout << str1 << endl;   // 1abcd
    str1.insert(2, "222");
    cout << str1 << endl;   // 1a222bcd
    str1.insert(str1.begin(), '0');
    cout << str1 << endl;   // 01a222bcd

    string str2 {"5555"};
    str1.insert(str1.end(), str2.begin(), str2.end());
    cout << str1 << endl;   // 01a222bcd5555
    str1.insert(str1.begin(), 5, '6');
    cout << str1 << endl;   // 6666601a222bcd5555
}

void test_delete()
{
    string str1 = "1234567890";
    str1.erase(1, 3);
    cout << str1 << endl;  // 1567890

    str1.erase(str1.begin(), str1.begin() + 2);
    cout << str1 << endl;  // 67890

    str1.erase(str1.begin());
    cout << str1 << endl;  // 7890

    str1.pop_back();
    cout << str1 << endl;  // 789
}

void test_modify()
{
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
}

void test_conversion()
{
    string str1 = "abcd";
    const char* str2 = str1.c_str();
    cout << str2 << endl;  // abcd

    const char* str3 = str1.data();
    cout << str3 << endl;  // abcd
}

void test_getline()
{
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
}

void test_number_conversion()
{
    string str1 = "1234";
    int i1 = stoi(str1);
    cout << i1 << endl;

    string str2 = to_string(i1);
    cout << str2 << endl;
}

void test_substring()
{
    string email = "1234567890@qq.com";
    int pos = email.find('@');
    string qq = email.substr(0, pos);
    cout << qq << endl;  // 1234567890
}

void test()
{
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
}

int main()
{
//    test_assign_swap();
//    test_append_insert();
//    test_delete();
//    test_modify();
//    test_conversion();
//    test_getline();
//    test_number_conversion();
//    test_substring();
    test();

    return 0;
}
