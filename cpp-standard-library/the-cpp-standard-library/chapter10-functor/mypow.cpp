#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <cmath>
using namespace std;
using namespace std::placeholders;

template <typename T1, typename T2>
struct mypow
{
    T1 operator() (T1 base, T2 exp) const
    {
        return std::pow(base, exp);
    }
};

void test()
{
    vector<int> coll {1,2,3,4,5,6,7,8,9};

    transform(coll.begin(), coll.end(),
              ostream_iterator<double>(cout, " "),
              bind(mypow<double, int>(), _1, 3));
    cout << endl;  // 1 8 27 64 125 216 343 512 729
}

int main()
{
    test();

    return 0;
}
