#include <iostream>
#include <queue>
using namespace std;

void test1()
{
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);

    cout << q.back() << endl;
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    cout << q.size() << endl;
}

int main()
{
    test1();
    return 0;
}
