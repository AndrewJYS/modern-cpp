#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>
using namespace std;

void test()
{
    vector<int> v1 {1,2,3,4,5,6,7,8,9};
    auto pos = v1.begin() + 2;
    rotate(v1.begin(), pos, v1.end());
    for_each(v1.cbegin(), v1.cend(), [](int val){ cout << val << " "; });
    cout << endl;  // 3 4 5 6 7 8 9 1 2

    vector<int> v2;
    v2.resize(v1.size());
    rotate_copy(v1.begin(), v1.begin()+3, v1.end()-2, v2.begin());
    for_each(v2.cbegin(), v2.cend(), [](int val){ cout << val << " "; });
    cout << endl;  // 6 7 8 9 3 4 5 0 0
}

int main()
{
    test();

    return 0;
}
