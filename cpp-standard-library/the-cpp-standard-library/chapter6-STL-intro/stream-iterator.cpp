#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main()
{
    vector<string> coll;

    copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(coll));
    // end with 'Enter' and 'ctrl+C'
    sort(coll.begin(), coll.end());
    unique_copy(coll.cbegin(), coll.cend(), ostream_iterator<string>(cout, " "));

    return 0;
}
