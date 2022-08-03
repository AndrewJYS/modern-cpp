#include <type_traits>

template <typename T1, typename T2,
          typename RT = typename std::decay_t<decltype(true? T1(): T2())>::type>
RT maxdefault1(const T1& a, const T2& b)
{
    return b < a ? a : b;
}

template <typename T1, typename T2,
          typename RT = typename std::decay<decltype(true? std::declval<T1>(): std::declval<T2>())>::type>
RT maxdefault2(const T1& a, const T2& b)
{
    return b < a ? a : b;
}

template <typename T1, typename T2,
          typename RT = typename std::common_type<T1, T2>::type>
RT maxdefault3(const T1& a, const T2& b)
{
    return b < a ? a : b;
}
