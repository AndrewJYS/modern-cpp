#include <iostream>
using namespace std;

int main()
{
    pair<string, int> p1(string("tom"), 18);
    pair<string, int> p2 = make_pair("jerry", 18);
    cout << p1.first << " " << p1.second << endl;
    cout << p2.first << " " << p2.second << endl;

    return 0;
}
