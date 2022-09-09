#include <iostream>
using namespace std;

class Fraction
{
public:
    Fraction(int num, int den = 1)
        : m_numerator(num), m_denominator(den)
    { cout << "use ctor: " << num << "/" << den << endl; }

//    Fraction operator+(const Fraction& f) {
//        return Fraction(m_numerator * f.m_denominator + m_denominator * f.m_numerator, m_denominator * f.m_denominator);
//    }

    operator double() {
        cout << "use double()" << endl;
        return (double)m_numerator / m_denominator;
    }

    void print() {
        cout << (double)m_numerator / m_denominator << endl;
    }

private:
    int m_numerator;
    int m_denominator;
};

int main()
{
    Fraction f(2, 5);
    Fraction fp = f + 4;
    fp.print();

    return 0;
}
