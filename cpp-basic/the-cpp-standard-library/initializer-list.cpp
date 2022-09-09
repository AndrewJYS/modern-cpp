#include <iostream>
#include <vector>
#include <initializer_list>
#include <algorithm>
using namespace std;

void print(initializer_list<int> vals)
{
    for (auto p = vals.begin(); p!= vals.end(); ++p)
        cout << *p << " ";
    cout << endl;
}

void test_vector()
{
    vector<int> v1 {1,2,3,4};
    v1.insert(v1.begin() + 2, {10, 11});
    for (auto i : v1)
        cout << i << " ";
    cout << endl;
}

void test_max_min()
{
    cout << max( {1, 3, 5, 2} ) << endl;
    cout << min({1, 3, 5, 2}) << endl;
    cout << max({string("a"), string("b"), string("d"), string("c")}) << endl;
    cout << min({string("a"), string("b"), string("d"), string("c")}) << endl;
}

int main()
{
    print({1,2,3,4,5});
    test_vector();
    test_max_min();

    return 0;
}
