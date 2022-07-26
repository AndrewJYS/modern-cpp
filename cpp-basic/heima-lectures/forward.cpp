#include <iostream>
using namespace std;

template<typename T>
void func(const T & )
{
    cout << "const T &" << endl;
}

template<typename T>
void func(T & )
{
    cout << "T &" << endl;
}

template<typename T>
void func(const T && )
{
    cout << "T &&" << endl;
}

template<typename T>
void forward_val(T && tmp)
{
    func( std::forward<T>(tmp) );
}

int main()
{
    int a = 0;
    const int &b = 1;

    forward_val(a);
    forward_val(b);
    forward_val(111);

    return 0;
}
