#include <iostream>
#include <typeinfo>
using namespace std;

// 可变参数的模板函数
template<class ... T>  // T叫做模板参数包
void func(T... args)  // args叫做函数参数包
{
    // 使用 sizeof...()计算可变参数的参数个数
    cout << sizeof...(args) << endl;
}



// 参数包的展开

void func2() // 递归终止函数
{
    cout << "end" << endl;
}

template<class T1, class ... T2>
void func2(T1 first, T2 ... last)
{
    cout << first << " ";
    func2(last...); // 递归调用函数本身
}


// 继承方式展可变参数模板类
// 1.可变参数模板声明
// 2.递归继承模板类
// 3.边界条件

// 1.可变参数模板声明
template<class ...T> class Car{};

// 2.递归继承模板类
template <class Head, class ... Tail>
class Car<Head, Tail...>: public Car<Tail...>
{
public:
    Car()
    {
        cout << "type = " << typeid(Head).name() << ";  " ;
    }
};

// 3.边界条件
template<> class Car<>{};



int main()
{
    func<int>(10);                           // 1
    func<int, double>(10, 1.1);              // 2
    func<int, string, char>(1, "name", 'b'); // 3

    func2(1,2,3,4); // 1 2 3 4 end

    Car<int, char*, double> BMW;  //type = d;  type = Pc;  type = i;

    return 0;
}
