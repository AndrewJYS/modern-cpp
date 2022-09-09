#include <iostream>
using namespace std;

class Person
{
public:
    Person():age(0), name("") {}
    Person(int age_, string name_): age(age_), name(name_) {}
    void toString() { cout << name << " " << age << endl; }

private:
    int age;
    string name;
};

int main()
{
    Person pa {14, "john"};
    Person pb {15, "ann"};
    swap(pa, pb);
    pa.toString(); // ann 15

    return 0;
}
