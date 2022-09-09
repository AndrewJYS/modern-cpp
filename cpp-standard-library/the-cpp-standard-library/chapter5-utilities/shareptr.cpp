#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

void test_basic_operations()
{
    //initialize
    shared_ptr<string> pJohn1(new string{"john"});
    shared_ptr<string> pJohn2 = pJohn1;  // copy constructor
    shared_ptr<string> pAlen = make_shared<string>("alen");
    shared_ptr<string> pBob;
    pBob.reset(new string{"bob"});

    //modify
    (*pBob)[0] = 'B';
    pAlen->replace(0, 1, "A"); //use member function of std::string

    //dereference
    cout << *pAlen << endl; //Alen
    cout << *pBob << endl; //Bob

    //use_count()
    vector<shared_ptr<string>> names;
    names.push_back(pAlen);
    names.push_back(pAlen);
    names.push_back(pAlen);
    names.push_back(pAlen);
    cout << pAlen.use_count() << endl;  // 5

    //release
    names[0] = nullptr;
    cout << pAlen.use_count() << endl;  // 4
    names.resize(3);
    cout << pAlen.use_count() << endl;  // 3, names[0] = nullptr
    names[1].reset();
    cout << pAlen.use_count() << endl;  // 2
    pAlen.reset();
    cout << names[2].use_count() << endl;  // 1
    cout << pAlen.use_count() << endl;  // 0
}

void test_deleter()
{
    shared_ptr<string> pNico(new string{"Nico"},
                             [](string* p) {
                                cout << "delete " << *p << endl;
                                delete p;
                             });
    pNico = nullptr; // output: delete Nico
}

int main()
{
//    test_basic_operations();

    test_deleter();

    return 0;
}
