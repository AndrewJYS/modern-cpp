#include <iterator>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;
using namespace std::placeholders;

void test()
{
    vector<int> v {1,2,3,4,5};
    auto begin_ = v.rend();
    begin_--;
    cout << *begin_ << endl;  // reverse iterator on vector is also bidirectional
}

int main()
{
    test();

    return 0;
}
