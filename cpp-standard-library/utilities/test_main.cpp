#include "utilities-pair.h"

#include <functional>
#include <string>

void test_output_pair();


int main()
{   test_output_pair();

    return 0;
}


void test_output_pair()
{
    std::pair<int, std::string> p1(12, "names");
    std::cout << p1 << std::endl; //[12, names]

    std::cout << std::make_pair(15.7, '@') << std::endl; // [15.7, @]

    std::string s1 {"str1"};
    std::string s2 {"str2"};
    auto p2 = std::make_pair(std::move(s1), std::move(s2)); // s1, s2 are no longer used
    std::cout << p2 << std::endl; // [str1, str2]
    p2.second = "345";
    std::cout << s2.length() << std::endl; // 0

    std::string s3 {"str3"};
    std::string s4 {"str4"};
    auto p3 = std::make_pair(std::ref(s3), std::ref(s4));
    std::cout << p3 << std::endl; // [str3, str4]
    p3.second = "123";
    std::cout << s4 << std::endl; // 123

    std::string s5 {"str5"};
    std::string s6 {"str6"};
    auto p4 = std::make_pair(std::cref(s5), std::cref(s6));
    std::cout << p4 << std::endl; // [str5, str6]
    //p4.second = "123"; // err
}
