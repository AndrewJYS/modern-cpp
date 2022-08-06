#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// 函数对象适配器
class MyPrint: public binary_function<int, int, void>
{ // 有两个参数，继承binary_function，尖括号<>中指明operator的参数类型和它的返回值
public:
    void operator()(int val, int start) const
    { // 加上const是因为父类中已经重载了operator，这里是重写父类函数，要与父类保持一致
        cout << val + start << " ";
    }
};

void test1()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    cout << "Please enter start: " ;
    int num;
    cin >> num;
    for_each(v.begin(), v.end(), bind2nd(MyPrint(), num)); // 函数对象适配器 bind2nd()
    /*
    Please enter start: 100
    100 101 102 103 104 105 106 107 108 109
    */
}

// 取反适配器
class greaterThan5: public unary_function<int, bool>
{
public:
    bool operator()(int val) const
    {
        return val > 5;
    }
};

void test2()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    vector<int>::iterator pos = find_if(v.begin(), v.end(), not1(greaterThan5()));
    // 一元取反适配器 not1(), 继承unary_function<类型, 返回值类型>，加const
    if (pos != v.end())
        cout << "the number less than 5 is " << *pos << endl;
        // the number less than 5 is 0 （因为是从0开始搜索的，取第一个小于5的数就是0）
    else
        cout << "not found" << endl;

    // 上述写法等价于下面
    vector<int>::iterator pos2 = find_if(v.begin(), v.end(), not1(bind2nd(greater<int>(), 5)));
    // 一元取反适配器 not1(),继承unary_function<类型, 返回值类型>
    if (pos2 != v.end())
        cout << "the number less than 5 is " << *pos2 << endl;
        // the number less than 5 is 0 （因为是从0开始搜索的，取第一个小于5的数就是0）
    else
        cout << "not found" << endl;
}

//函数指针适配器
void MyPrint3(int val, int start)
{
    cout << val + start << " ";
}

void test3()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    cout << "Please enter start: " ;
    int num;
    cin >> num;
    // 函数指针适配器，将 函数指针 适配成 函数对象
    for_each(v.begin(), v.end(), bind2nd(ptr_fun(MyPrint3), num));
    /*
    Please enter start: 100
    100 101 102 103 104 105 106 107 108 109
    */
}

// 成员函数适配器
class Person
{
public:
    Person(string name, int age)
    {
        this->m_name = name;
        this->m_age = age;
    }

    void showInfo()
    {
        cout << "member function----name: " << m_name << "; age: " << m_age << endl;
    }

    void plusAge()
    {
        m_age++;
    }

    string m_name;
    int m_age;
};

void PrintPerson(Person& p)
{
    cout << "name: " << p.m_name << "; age: " << p.m_age << endl;
}

void test4()
{
    vector<Person> v;
    Person p1("a", 15);
    Person p2("b", 25);
    Person p3("c", 20);
    Person p4("d", 10);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    for_each(v.begin(), v.end(), PrintPerson);
    /*
    name: a; age: 15
    name: b; age: 25
    name: c; age: 20
    name: d; age: 10
    */

    // 成员函数适配器
    for_each(v.begin(), v.end(), mem_fun_ref(&Person::showInfo));
    /*
    member function----name: a; age: 15
    member function----name: b; age: 25
    member function----name: c; age: 20
    member function----name: d; age: 10
    */

    for_each(v.begin(), v.end(), mem_fun_ref(&Person::plusAge));
    for_each(v.begin(), v.end(), mem_fun_ref(&Person::showInfo));
    /*
    member function----name: a; age: 16
    member function----name: b; age: 26
    member function----name: c; age: 21
    member function----name: d; age: 11
    */

}

int main()
{
    //test1();
    //test2();
    //test3();
    test4();
    return 0;
}
