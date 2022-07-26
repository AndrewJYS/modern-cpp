#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> v;
    for (int i = 1; i < 5; i++)
    {
        v.push_back(i);
    }

    for (auto& tmp: v)
    {
        tmp *= 2;
    }

    for (auto tmp: v)
    {
        cout << tmp << " ";
    }
    cout << endl; //2 4 6 8

    return 0;
}
