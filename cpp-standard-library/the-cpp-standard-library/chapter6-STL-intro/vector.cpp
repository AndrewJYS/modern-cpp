#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

void C_style()
{
    vector<char> v;
    v.resize(41);
    strcpy(v.data(), "hello world");
    printf("%s\n", v.data());
}

void test_assign()
{
    vector<int> v1{1,2,3,4,5};
    v1.assign({7,8,9});
    copy(v1.cbegin(), v1.cend(), ostream_iterator<int>(cout, " "));
}

int main()
{
    C_style();
    test_assign();

    return 0;
}
