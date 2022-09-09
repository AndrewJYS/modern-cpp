#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>
#include <cmath>
using namespace std;
using namespace std::placeholders;

bool isPrime(int num)
{
    num = abs(num);
    if (0 == num || 1 == num) return false;

    int i;
    for (i = num / 2; num % i != 0; --i);
    return i == 1;
}

bool binaryIsPrime(int num, int)
{
    return isPrime(num);
}

void test()
{
    vector<int> v {1,5,4,7,9,13,23,31,7,37,40,47,3,5};
    auto pos1 = search_n(v.begin(), v.end(), 3, 0, bind(binaryIsPrime, _1, 0));
    auto pos2 = search_n(v.begin(), v.end(), 3, 0, binaryIsPrime);

    cout << *pos1 << endl; // 13
    cout << *pos2 << endl; // 13
}

int main()
{
    test();

    return 0;
}
