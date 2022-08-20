#include <iostream>
#include <string>

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


int main()
{
    test_basic_operations();

    return 0;
}
