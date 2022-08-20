#ifndef STACK1_HPP_INCLUDED
#define STACK1_HPP_INCLUDED

#include <vector>
#include <cassert>
#include <iostream>
#include <deque>
#include <string>

template<typename T>
class Stack
{
private:
    std::vector<T> elems;

public:
    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const { return elems.empty(); }

//    void printOn(std::ostream& strm) const {
//        for (T const& elem : elems) {
//            strm << elem << ' '; // call << for each element
//        }
//    }
//
//    friend std::ostream& operator<< (std::ostream& strm, Stack<T> const& s)
//    {
//        s.printOn(strm);
//        return strm;
//    }
//
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, Stack<U> const& s);

};

template<typename T>
void Stack<T>::push(T const& elem)
{
    elems.push_back(elem);
}

template<typename T>
void Stack<T>::pop()
{
    assert(!elems.empty());
    elems.pop_back();
}

template<typename T>
T const& Stack<T>::top() const
{
    assert(!elems.empty());
    return elems.back();
}

template<typename U>
std::ostream& operator<<(std::ostream& out, Stack<U> const& s)
{
    out << "overloaded opaerator <<: ";
    for (U const& elem: s.elems)
    {
        out << elem << " ";
    }
    return out;
}



template<>
class Stack<std::string>
{
private:
    std::deque<std::string> elems;

public:
    void push(std::string const&);
    void pop();
    std::string const& top() const;
    bool empty() const { return elems.empty(); }
    void printStack();

    friend std::ostream& operator<<(std::ostream& out, Stack<std::string> const& s);
};

void Stack<std::string>::push(std::string const& elem)
{
    elems.push_back(elem);
}

void Stack<std::string>::pop()
{
    assert(!elems.empty());
    elems.pop_back();
}

std::string const& Stack<std::string>::top() const
{
    assert(!elems.empty());
    return elems.back();
}

void Stack<std::string>::printStack()
{
    std::cout << "member function for print: ";
    for (std::string const& elem: elems)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& out, Stack<std::string> const& s)
{
    out << "overloaded opaerator <<: ";
    for (std::string const& elem: s.elems)
    {
        out << elem << " ";
    }
    return out;
}


template<typename T>
class Stack<T*>
{
private:
    std::vector<T*> elems;

public:
    void push(T*);
    T* pop();
    T* top() const;
    bool empty() const { return elems.empty(); }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, Stack<U*> const& s);
};

template<typename T>
void Stack<T*>::push(T* elem)
{
    elems.push_back(elem);
}

template<typename T>
T* Stack<T*>::pop()
{
    assert(!elems.empty());
    T* p = elems.back();
    elems.pop_back();
    return p;
}

template<typename T>
T* Stack<T*>::top() const
{
    assert(!elems.empty());
    return elems.back();
}

template<typename U>
std::ostream& operator<<(std::ostream& out, Stack<U*> const& s)
{
    out << "overloaded opaerator <<: ";
    for (U* elem: s.elems)
    {
        out << *elem << " ";
    }
    return out;
}

#endif // STACK1_HPP_INCLUDED
