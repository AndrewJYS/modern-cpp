#include "stack1.hpp"

int main()
{
    Stack<std::string> strStack;
    strStack.push("hello");
    strStack.push("world");
    std::cout << strStack << std::endl;  //overloaded opaerator <<: hello world
    strStack.printStack();               //member function for print: hello world

    Stack<int> intStack;
    intStack.push(3);
    intStack.push(7);
    std::cout << intStack << std::endl;  //overloaded opaerator <<: 3 7
    //intStack.printStack(); // error, printStack() is not a member function of intStack

    Stack<double*> dptrStack;
    dptrStack.push(new double{5.2});
    dptrStack.push(new double{4.9});
    std::cout << dptrStack << std::endl; //overloaded opaerator <<: 5.2 4.9

    return 0;
}
