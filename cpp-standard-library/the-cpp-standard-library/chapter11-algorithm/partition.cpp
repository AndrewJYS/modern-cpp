#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
using namespace std;

class Even
{
public:
    bool operator()(int val)
    {
        return val % 2 == 0;
    }
};

void print(int val)
{
    cout << val << " ";
}

void test1()
{
    vector<int> v1 {3,5,4,7,2,9,8,6,1,10};
    vector<int> v2(v1);

    partition(v1.begin(), v1.end(), Even());
    for_each(v1.cbegin(), v1.cend(), print);
    cout << endl; // 10 6 4 8 2 9 7 5 1 3

    stable_partition(v2.begin(), v2.end(), Even());
    for_each(v2.cbegin(), v2.cend(), print);
    cout << endl; // 4 2 8 6 10 3 5 7 9 1
}

void test2()
{
    vector<int> v1 {3,5,4,7,2,9,8,6,1,10};
    vector<int> oddcoll;
    vector<int> evencoll;

    partition_copy(v1.begin(), v1.end(),
                   back_inserter(evencoll), back_inserter(oddcoll),
                   Even());
    for_each(oddcoll.cbegin(), oddcoll.cend(), print);  cout << endl;  // 3 5 7 9 1
    for_each(evencoll.cbegin(), evencoll.cend(), print);  cout << endl; // 4 2 8 6 10
}

int main()
{
    test2();

    return 0;
}
