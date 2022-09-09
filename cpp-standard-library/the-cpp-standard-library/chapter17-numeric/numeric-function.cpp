#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

void test_numeric()
{
    cout << pow(2, 6) << endl;
    cout << sqrt(64) << endl;
    cout << ceil(3.6) << endl;
    cout << ceil(4) << endl;
    cout << floor(3) << endl;
    cout << floor(3.5) << endl;
    cout << fabs(-4.5) << endl;     // 4.5

    cout << abs(-9.6) << endl;      // 9.6
    cout << labs(-4.6) << endl;     // 4
    cout << llabs(-9.5) << endl;    // 9
}

void test_rand()
{
    srand((unsigned)time(0));
    int a = rand()% 10 + 1;
    cout << a << endl;
}

int main()
{
    test_rand();

    return 0;
}
