#include <iostream>
using namespace std;

int main()
{
    // nullptr为了解决NULL的二义性
    int a = NULL;
    int* pa = NULL;

    int *pb = nullptr;
    // int b = nullptr; // 报错

    if (pa == pb)
        cout << "equal" << endl; // equal

    return 0;
}
