#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
    list<int> coll1 {1,2,3,4,5,6,7};

    vector<int> coll2;
    copy(coll1.cbegin(), coll1.cend(), back_inserter(coll2));
    for_each(coll2.cbegin(), coll2.cend(), [](int val){ cout << val << " "; });
    cout << endl; // 1 2 3 4 5 6 7

    deque<int> coll3;
    copy(coll1.cbegin(), coll1.cend(), front_inserter(coll3));
    for_each(coll3.cbegin(), coll3.cend(), [](int val){ cout << val << " "; });
    cout << endl; // 7 6 5 4 3 2 1

    set<int> coll4;
    copy(coll1.cbegin(), coll1.cend(), inserter(coll4, coll4.begin()));
    for_each(coll4.cbegin(), coll4.cend(), [](int val){ cout << val << " "; });
    cout << endl; // 1 2 3 4 5 6 7

    return 0;
}
