#include <iostream>
#include <string>
using namespace std;

class Foo
{
public:
    int m_id;
    long m_data;
    string m_str;

public:
    Foo():m_id(0) { cout << "default ctor.this=" << this << " id=" << m_id << endl; }
    Foo(int i):m_id(i) { cout << "default ctor.this=" << this << " id=" << m_id << endl; }

    ~Foo() {cout << "dtor.this=" << this << " id=" << m_id << endl; }

    static void* operator new(size_t size);
    static void* operator new[](size_t size);
    static void operator delete(void* ptr, size_t size);
    static void operator delete[](void* ptr, size_t size);
};

void* Foo::operator new(size_t size)
{
    Foo* p = (Foo*)malloc(size);
    cout << "member operator new(); allocate size: " << size << endl;
    return p;
}

void Foo::operator delete(void* ptr, size_t size)
{
    cout << "member operator delete(), release size: " << size << endl;
    free(ptr);
}

void* Foo::operator new[](size_t size)
{
    Foo* p = (Foo*)malloc(size);
    cout << "member operator new[](); allocate size: " << size << endl;
    return p;
}

void Foo::operator delete[](void* ptr, size_t size)
{
    cout << "member operator delete[](), release size: " << size << endl;
    free(ptr);
}

int main()
{
    Foo* p = new Foo(7);
    delete p;
    cout << endl;

    Foo* pArray = new Foo[3];
    delete [] pArray;
    cout << endl;

    Foo* g_p = ::new Foo(12);
    ::delete g_p;
    cout << endl;

    return 0;
}
