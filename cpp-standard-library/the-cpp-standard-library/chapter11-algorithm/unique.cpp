#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
using namespace std;
using namespace std::placeholders;

class cmp
{
public:
    bool operator()(int a, int b)
    {
        return (a + b) > 9;
    }
};

void test()
{
    vector<int> v{1,4,6,8,10,5,3,7,8,6};
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;  // 1 4 6 8 10 5 3 7 8 6

    auto pos = unique(v.begin(), v.end(), bind(cmp(), _1, _2));
    v.erase(pos, v.end());
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;  // 1 4 5 3 6
}

int main()
{
    test();

    return 0;
}
