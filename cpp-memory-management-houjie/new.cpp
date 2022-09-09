#include <iostream>
using namespace std;

class Test
{
public:
    Test() { printf("this is constructor\n"); }
    Test(int val) { printf("this is constructor, %d\n", val); }
    ~Test() { printf("this is destructor\n"); }
};

int main()
{
    Test* test1 = new Test(); //this is constructor
    delete test1; //this is destructor

    void* buff = operator new(sizeof(Test));

    void* testBuff = malloc(12);
    Test* test2 = new (testBuff)Test(12); //this is constructor, 12
    delete test2; //this is destructor

    return 0;
}
