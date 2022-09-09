#include <iostream>
using namespace std;

class MyFunctor
{
public:
    MyFunctor(int i): r(i) {}

    int operator()(int tmp)
    {
        return tmp + r;
    }

private:
    int r;
};

int main()
{
    MyFunctor mf(10);
    cout << mf(1) << endl;

    return 0;
}
