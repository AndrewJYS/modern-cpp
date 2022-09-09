#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;
using namespace std::placeholders;

void test_bind1()
{
    auto plus10 = bind(plus<int>(), _1, 10);
    cout << "7+10: " << plus10(7) << endl; //7+10: 17

    auto plus10times2 = bind(multiplies<int>(), plus10, 2);
    cout << "(7+10)*2: " << plus10times2(7) << endl; // (7+10)*2: 34

    auto pow3 = bind(multiplies<int>(),
                     bind(multiplies<int>(), _1, _1),
                     _1);
    cout << "7*7*7: " << pow3(7) << endl; // 7*7*7: 343

    auto inversDivide = bind(divides<double>(), _2, _1);
    cout << "7/49: " << inversDivide(49, 7) << endl; // 7/49: 0.142857
}

void test_bind2()
{
    vector<int> coll {1,2,3,4,5,6,7};
    transform(coll.begin(), coll.end(),
              coll.begin(),
              bind(plus<int>(), _1, 10));
    for_each(coll.cbegin(), coll.cend(), [](int val){ cout << val << " "; });
    cout << endl; // 11 12 13 14 15 16 17
}


void MyPrint3(int val, int start)
{
    cout << val + start << " ";
}

void test_bind3()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    cout << "Please enter start: " ;
    int num;
    cin >> num;
    for_each(v.cbegin(), v.cend(), bind(MyPrint3, _1, num));
    /*
    Please enter start: 100
    100 101 102 103 104 105 106 107 108 109
    */
}


class Person
{
public:
    Person(string name, int age):
        m_name(name), m_age(age)
    { }

    void print1() const {
        cout << "mf, name: " << m_name << "; age: " << m_age << endl;
    }

    void print2(const string& prefix) const {
        cout << prefix << m_name << "; age: " << m_age << endl;
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

void test_bind4()
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
    for_each(v.begin(), v.end(), bind(&Person::print1, _1));
    /*
    mf, name: a; age: 15
    mf, name: b; age: 25
    mf, name: c; age: 20
    mf, name: d; age: 10
    */

    for_each(v.begin(), v.end(), bind(&Person::plusAge, _1));
    for_each(v.begin(), v.end(), bind(&Person::print2, _1, "Person: "));
    /*
    Person: a; age: 16
    Person: b; age: 26
    Person: c; age: 21
    Person: d; age: 11
    */

    for_each(v.begin(), v.end(), mem_fn(&Person::print1));
    /*
    mf, name: a; age: 16
    mf, name: b; age: 26
    mf, name: c; age: 21
    mf, name: d; age: 11
    */
}

int main()
{
    test_bind4();

    return 0;
}
