# special containers  

The C++ standard library provides not only the containers for the STL framework but also some containers that fit some special needs and provide simple, almost self-explanatory, interfaces. You can group these containers into either the so-called container adapters, which adapt standard STL containers to fit special needs, or a bitset, which is a containers for bits or Boolean values. **There are three standard container adapters: stacks, queues, and priority queues**.  

## stack  

In \<stack\>, the class stack is defined as follows:  

```cpp
namespace std {
    template <typename T,
    typename Container = deque<T>>
    class stack;
}
```

The core interface of stacks is provided by the member functions **push(), top(), and pop()**:  
• push() inserts an element into the stack.  
• top() returns the next element in the stack.  
• pop() removes an element from the stack.  

Note that **pop() removes the next element but does not return it**, whereas **top() returns the next element without removing it**. Note that the behavior of **top() and pop() is undefined if the stack contains no elements. The member functions size() and empty() are provided to check whether the stack contains elements**.  

## queue  

In \<queue\>, the class queue is defined as follows:  

```cpp
namespace std {
    template <typename T,
    typename Container = deque<T>>
    class queue;
}
```

The core interface of queues is provided by the member functions **push(), front(), back() and pop()**:  
• push() inserts an element into the queue.  
• front() returns the next element in the queue (the element that was inserted first).  
• back() returns the last element in the queue (the element that was inserted last).  
• pop() removes an element from the queue.  

Note that **pop() removes the next element but does not return it**, whereas **front() and back() return the element without removing it**. Note that the behavior of **front(), back(), and pop() is undefined if the queue contains no elements. The member functions size() and empty() are provided to check whether the queue contains elements**.  

## priority_queue  

The class priority_queue<> implements a queue from which elements are read according to their priority.  

In \<queue\>, the class priority_queue is defined as follows:  

```cpp
namespace std {
    template <typename T,
    typename Container = vector<T>,
    typename Compare = less<typename Container::value_type>>
    class priority_queue;
}
```

The first template parameter is the type of the elements. The optional second template parameter defines the container that the priority queue uses internally for its elements. The default container is a vector. The **optional third template parameter defines the sorting criterion** used to find the next element with the highest priority. By default, this parameter compares the elements by using operator <.  

To define your own sorting criterion, you must pass a function, a function object, or a lambda as a binary predicate that is used by the sorting algorithms to compare two elements. For example, the following declaration defines a priority queue with reverse sorting:  

```cpp
std::priority_queue<float,std::vector<float>, std::greater<float>> pbuffer;
```

The core interface of priority queues is provided by the member functions **push(), top(), and pop()**:  
• push() inserts an element into the priority queue.  
• top() returns the next element in the priority queue.  
• pop() removes an element from the priority queue.  

As for the other container adapters, **pop() removes the next element but does not return it**, whereas **top() returns the next element without removing it**. Thus, you must always call both functions to process and remove the next element from the priority queue. And, as usual, the behavior of **top() and pop() is undefined if the priority queue contains no elements. If in doubt, you must use the member functions size() and empty()**.  

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 7.12  
