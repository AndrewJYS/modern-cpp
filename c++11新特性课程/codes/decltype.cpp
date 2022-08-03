#include <iostream>
#include <typeinfo>
#include <vector>
using namespace std;

int main()
{
    // decltyp用来获取变量的类型
    int i;
    decltype(i) j = 0;
    cout << typeid(j).name() << endl; // i(int)

    // decltype(a + b)
    float a;
    double b;
    decltype(a + b)c;
    cout << typeid(c).name() << endl; // d(double)

    // 迭代器
    vector<int> v(5, 10);
    decltype(v.begin()) k;
    for (k = v.begin(); k != v.end(); k++)
        cout << *k << " ";
    cout << endl; // 10 10 10 10 10

    return 0;
}
