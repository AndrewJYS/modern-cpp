#include "max1.hpp"
#include "maxauto.hpp"
#include "maxcommon.hpp"
#include "maxdefault.hpp"
#include "void_template.hpp"
#include "MyString.hpp"
#include <iostream>
#include <string>

void test_max1();
void test_void_template();
void test_maxauto();
void test_maxcommon();
void test_default();


int main()
{
	test_max1();
	test_void_template();
	test_maxauto();
	test_maxcommon();
	test_default();

	return 0;
}


void test_max1()
{
	int i = 42;
    std::cout << "max(7,i): " << ::max(7,i) << '\n'; //max(7,i): 42

    double f1 = 3.4;
    double f2 = -6.7;
    std::cout << "max(f1,f2): " << ::max(f1,f2) << '\n'; // max(f1,f2): 3.4

    std::string s1 = "mathematics";
    std::string s2 = "math";
    std::cout << "max(s1,s2): " << ::max(s1,s2) << '\n'; // max(s1,s2): mathematics

    MyString mystr1("abc");
    MyString mystr2("bcd");
    std::cout << "max(mystr1, mystr2): " << ::max(mystr1, mystr2) << '\n'; // max(mystr1, mystr2): bcd

    std::cout << std::endl;
}

void test_void_template()
{
	void* p = nullptr;
	::foo(p); // foo
}

void test_maxauto()
{
    int i = 42;
    std::cout << "max(7,i): " << ::max(7,i) << '\n'; //max(7,i): 42

    double f1 = 3.4;
    double f2 = -6.7;
    std::cout << "max(f1,f2): " << maxauto(f1,f2) << '\n'; // max(f1,f2): 3.4

    std::cout << std::endl;
}

void test_maxcommon()
{
    int i = 42;
    std::cout << "max(7,i): " << ::max(7,i) << '\n'; //max(7,i): 42

    double f1 = 3.4;
    double f2 = -6.7;
    std::cout << "max(f1,f2): " << maxcommon(f1,f2) << '\n'; // max(f1,f2): 3.4

    std::cout << std::endl;
}

void test_default()
{
    int i = 42;
    //std::cout << "max(7,i): " << maxdefault1(7,i) << '\n'; //err, no matching function for call to 'maxdefault(int, int&)'
    std::cout << "max(7,i): " << maxdefault2(7,i) << '\n';
    std::cout << "max(7,i): " << maxdefault3(7,i) << '\n';
}
