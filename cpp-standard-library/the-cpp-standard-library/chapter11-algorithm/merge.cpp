#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>
using namespace std;

void test()
{
    vector<int> v1 {1,2,4,6,8};
    vector<int> v2 {3,5,6,9,10};
    vector<int> v3;
    v3.resize(v1.size() + v2.size());
    vector<int> v4;
    v4.resize(v1.size() + v2.size());

    merge(v1.begin(), v1.end(),
          v2.begin(), v2.end(),
          v3.begin());
    for_each(v3.cbegin(), v3.cend(), [](int val){ cout << val << " "; });
    cout << endl; // 1 2 3 4 5 6 6 8 9 10

    merge(v1.begin(), v1.end(),
          v2.begin(), v2.end(),
          v4.begin(), greater<int>());
    for_each(v4.cbegin(), v4.cend(), [](int val){ cout << val << " "; });
    cout << endl; //
}

int main()
{
    test();

    return 0;
}
