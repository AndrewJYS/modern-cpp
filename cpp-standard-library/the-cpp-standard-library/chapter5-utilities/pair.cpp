#include <iostream>
#include <string>
#include <functional>

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& p)
{
    out << '[' << p.first << ", " << p.second << ']';
    return out;
}

void test_basic_operations()
{
    std::pair<int, int> i_pair1;
    std::pair<int, int> i_pair2(2, 3);

    std::string a = "hello";
    std::string b = "world";
    std::pair<std::string, std::string> s_pair1(std::move(a), std::move(b));

    std::pair<std::string, std::string> s_pair2(s_pair1);
    std::cout << s_pair2 << std::endl; // [hello, world]

    std::pair<std::string, std::string> s_pair3(std::move(s_pair1));
    std::cout << s_pair1 << std::endl; // [, ]

    i_pair1 = i_pair2;

    std::pair<int, int> i_pair3;
    i_pair3 = std::move(i_pair2);

    std::cout << i_pair1.first << " " << i_pair1.second << std::endl;

    if (i_pair1 == i_pair3)
        std::cout << "i_pair1 is the same as i_pair3" << std::endl;
        //output:  i_pair1 is the same as i_pair3

    std::pair<int, int> i_pair4(1, 2);
    std::pair<int, int> i_pair5(3, 4);
    i_pair4.swap(i_pair5);
    std::cout << i_pair5 << std::endl; // [1, 2]

    swap(i_pair4, i_pair5);
    std::cout << i_pair5 << std::endl; // [3, 4]

    std::cout << std::make_pair(15.7, '@') << std::endl; // [15.7, @]
}

void test_make_pair()
{
    std::string s1 {"str1"};
    std::string s2 {"str2"};
    auto p1 = std::make_pair(std::move(s1), std::move(s2)); // s1, s2 are no longer used
    std::cout << p1 << std::endl; // [str1, str2]
    p1.second = "345";
    std::cout << s2.length() << std::endl; // 0

    std::string s3 {"str3"};
    std::string s4 {"str4"};
    auto p2 = std::make_pair(std::ref(s3), std::ref(s4));
    std::cout << p2 << std::endl; // [str3, str4]
    p2.second = "123";
    std::cout << s4 << std::endl; // 123

    std::string s5 {"str5"};
    std::string s6 {"str6"};
    auto p3 = std::make_pair(std::cref(s5), std::cref(s6));
    std::cout << p3 << std::endl; // [str5, str6]
    //p4.second = "123"; // err
}

int main()
{
    //test_basic_operations();
    test_make_pair();

    return 0;
}
