#include <iostream>
#include <stack>
using namespace std;

void test1()
{
    stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);

    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    cout << s.size() << endl;
}

int main()
{
    test1();
    return 0;
}
