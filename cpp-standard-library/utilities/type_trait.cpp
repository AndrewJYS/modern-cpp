#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <string>

template <typename T>
void foo(const T& val)
{
    if (std::is_pointer<T>::value) {
        std::cout << "foo() called for a pointer" << std::endl;
    }
    else {
        std::cout << "foo() called for a value" << std::endl;
    }
}

// 重载版本
template<typename T>
void foo_impl(const T& val, std::true_type)
{
    std::cout << "foo() called for a pointer" << std::endl;
}

template<typename T>
void foo_impl(const T& val, std::false_type)
{
    std::cout << "foo() called for a value" << std::endl;
}

template<typename T>
void foo_adv(const T& val)
{
    foo_impl(val, std::is_pointer<T>());
}


void test_is_pointer()
{
    int* pi = new int{5};
    foo(pi); // foo() called for a pointer

    int i_val = {4};
    foo(i_val); // foo() called for a value

    //调用重载版本
    foo_adv(pi); // foo() called for a pointer
    foo_adv(i_val); // foo() called for a value
}

template <typename T1, typename T2>
typename std::common_type<T1, T2>::type min_(const T1& val1, const T2& val2)
{
    return (val1 < val2) ? val1 : val2;
}

int main()
{
    test_is_pointer();

    std::cout << min_(11525.24, 1252) << std::endl;

    return 0;
}
