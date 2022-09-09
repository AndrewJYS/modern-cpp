#include <iostream>
#include <algorithm>
#include <list>
#include <iterator>
using namespace std;

int main()
{
    list<int> coll;

    for (int i = 1; i <= 6; ++i) {
        coll.push_back(i);
        coll.push_front(i);
    }
    cout << "pre:  ";
    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    auto end = remove(coll.begin(), coll.end(), 3);

    cout << "post: ";
    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    // print number of removed elements
    cout << "number of removed elements: " << distance(end,coll.end()) << endl;

    // remove ‘‘removed’’ elements
    coll.erase(end, coll.end());

    // print all elements of the modified collection
    copy (coll.cbegin(), coll.cend(), ostream_iterator<int>(cout," "));
    cout << endl;

    return 0;
}
