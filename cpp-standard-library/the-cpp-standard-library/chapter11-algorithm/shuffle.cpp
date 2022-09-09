#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

void test()
{
    vector<int> v {0,1,2,3,4,5,6,7,8,9};

    random_shuffle(v.begin(), v.end());
    for_each(v.begin(), v.end(), [](int val){cout << val << " ";});
    cout << endl;  // 8 1 9 2 0 5 7 3 4 6
}

int main()
{
    srand((unsigned int)time(NULL));
    test();

    return 0;
}
