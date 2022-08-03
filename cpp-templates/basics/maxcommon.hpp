#include <type_traits>

template <typename T1, typename T2>
typename std::common_type<T1, T2>::type maxcommon(const T1& a, const T2& b)
{
    return b < a ? a : b;
}
