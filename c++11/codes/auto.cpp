#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;

int main()
{
    // 注意：auto在定义变量时，必须初始化
    // 有些IDE不支持函数形参是auto变量
    // auto变量不能作为自定义类型的成员变量。比如struct test{auto a = 10;};
    // 不能定义auto数组。比如，auto b[2] = {1, 2};
    // 模板实例化类型不能是auto类型。比如，vector<auto> b = {1};

    auto a = 1; // int
    auto b = 1.444; // double
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;

    vector<int> v(5, 10);
    for (auto it = v.begin(); it != v.end(); it++)
        cout << *it << " ";
    cout << endl; // 10 10 10 10 10

    return 0;
}
