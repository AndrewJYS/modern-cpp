#include <iostream>
using namespace std;

struct Test
{
    int a;
    double b;
    char c[10];
};

int main()
{
    int a{1};
    int b = {1};
    Test test = {1, 1.3, "name"};
    int arr1[] = {1, 2};
    int arr2[]{1, 2};

    cout << a << endl;
    cout << b << endl;
    cout << test.a << " " << test.b << " " << test.c << endl;

    int ta = 1024;
    char tb{a};
    cout << tb << endl;

    return 0;
}
