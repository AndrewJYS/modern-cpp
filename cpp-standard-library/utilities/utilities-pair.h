#ifndef UTILITIES_PAIR_H_INCLUDED
#define UTILITIES_PAIR_H_INCLUDED

#include <iostream>

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& p)
{
    out << '[' << p.first << ", " << p.second << ']';
    return out;
}

#endif // UTILITIES-PAIR_H_INCLUDED
