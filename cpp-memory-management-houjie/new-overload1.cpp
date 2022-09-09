#include <iostream>
using namespace std;

void* myAlloc(size_t size)
{
    return malloc(size);
}

void myFree(void* ptr)
{
    return free(ptr);
}

inline void* operator new(size_t size)
{
    cout << "this is my global operator new() \n";
    return myAlloc(size);
}

inline void operator delete(void* ptr)
{
    cout << "this is my global operator delete()\n";
    return myFree(ptr);
}

class Test
{
public:
    Test() { printf("this is constructor\n"); }
    Test(int val) { printf("this is constructor, %d\n", val); }
    ~Test() { printf("this is destructor\n"); }
};

int main()
{
    Test* test1 = new Test();
    delete test1;

    return 0;
}
