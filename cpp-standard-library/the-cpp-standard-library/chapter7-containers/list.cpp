#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;


bool cmp(int& a, int& b)
{
    return (a + b) > 10;
}

void test_unique()
{
    list<int> L1 {1,4,4,4,5,6,7,7};
    L1.unique();
    for_each(L1.cbegin(), L1.cend(), [](int val){ cout << val << " "; });
    cout << endl;
    //1 4 5 6 7

    list<int> L2 {1,5,6,7,8,9,4,10,11};
    L2.unique(cmp);
    for_each(L2.cbegin(), L2.cend(), [](int val){ cout << val << " "; });
    cout << endl;
    // 1 5 4
}

void test_merge()
{
    list<int> L1 {1,4,5,6};
    list<int> L2 {2,5,6,8};
    L1.merge(L2);
    for_each(L1.cbegin(), L1.cend(), [](int val){ cout << val << " "; });
    cout << endl;
    // 1 2 4 5 5 6 6 8

    list<int> L3 {6,5,4,1};
    list<int> L4 {8,6,5,2};
    L3.merge(L4);
    for_each(L3.cbegin(), L3.cend(), [](int val){ cout << val << " "; });
    cout << endl;
    // 6 5 4 1 8 6 5 2，逆序不行

    list<int> L5 {1,4,5,6};
    list<int> L6 {2,5,6,8};
    L5.merge(L6, less<int>());
    for_each(L5.cbegin(), L5.cend(), [](int val){ cout << val << " "; });
    cout << endl;
    //1 2 4 5 5 6 6 8,  op要与L5,L6的排序op相同

    list<int> L7 {6,5,4,1};
    list<int> L8 {8,6,5,2};
    L7.merge(L8, greater<int>());
    for_each(L7.cbegin(), L7.cend(), [](int val){ cout << val << " "; });
    cout << endl;
    //8 6 6 5 5 4 2 1
}

int main()
{
//    test_unique();
    test_merge();

    return 0;
}
