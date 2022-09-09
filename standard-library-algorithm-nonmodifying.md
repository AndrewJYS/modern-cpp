# nonmodifying algorithms  

## Counting Elements  

```cpp
difference_type
count (InputIterator beg, InputIterator end, const T& value)

difference_type
count_if (InputIterator beg, InputIterator end, UnaryPredicate op)
```

• The first form counts the elements in the range [beg,end) that are equal to value value.  
• The second form counts the elements in the range [beg,end) for which the unary predicate op(elem) yields true.  
• The type of the return value, difference_type, is the difference type of the iterator:  

```cpp
typename iterator_traits<InputIterator>::difference_type
```

• Note that ***op should not change its state during a function call***.  
• **op should not modify the passed arguments**.  
• Associative and unordered containers provide a similar member function, count(), to count the number of elements that have a certain value as key.  
• **Complexity: linear** (numElems comparisons or calls of op(), respectively).  

```cpp
class MyCmp
{
public:
    bool operator()(int val)
    {
        return val > 4;
    }
};

void test()
{
    vector<int> v {4,4,4,5,6};

    // 统计元素个数
    cout << count(v.begin(), v.end(), 4) << endl; // 3

    // 按条件统计
    cout << count_if(v.begin(), v.end(), MyCmp()) << endl; // 2
}
```

## Minimum and Maximum  

```cpp
ForwardIterator
min_element (ForwardIterator beg, ForwardIterator end)

ForwardIterator
min_element (ForwardIterator beg, ForwardIterator end, CompFunc op)

ForwardIterator
max_element (ForwardIterator beg, ForwardIterator end)

ForwardIterator
max_element (ForwardIterator beg, ForwardIterator end, CompFunc op)

pair<ForwardIterator,ForwardIterator>
minmax_element (ForwardIterator beg, ForwardIterator end)

pair<ForwardIterator,ForwardIterator>
minmax_element (ForwardIterator beg, ForwardIterator end, CompFunc op)
```

• These algorithms return the position of the minimum, the maximum element, or a pair of the minimum and the maximum element in the range [beg,end).  
• **The versions without op compare the elements with operator <**.  
• op is used to compare two elements:  
op(elem1,elem2)  
It should return true when the first element is less than the second element.  
• **If more than one minimum or maximum element exists, min_element() and max_element() return the first found; minmax_element() returns the first minimum but the last maximum element**, so max_element() and minmax_element() don’t yield the same maximum element.  
• If the range is empty, the algorithms return beg or a pair<beg,beg>.  
• op should not modify the passed arguments.  
• **Complexity: linear** (numElems-1 comparisons or calls of op(), respectively, for min_element() and max_element() and 3/2(numElems-1) comparisons or calls of op(), respectively, for minmax_element()).  

## Searching Elements  

### Search First Matching Element  

```cpp
InputIterator
find (InputIterator beg, InputIterator end, const T& value)

InputIterator
find_if (InputIterator beg, InputIterator end, UnaryPredicate op)

InputIterator
find_if_not (InputIterator beg, InputIterator end, UnaryPredicate op)
```

• The first form returns the position of the first element in the range [beg,end) that has a value equal to value.  
• The second form returns the position of the first element in the range [beg,end) for which the unary predicate op(elem) yields true.  
• The third form (available since C++11) returns the position of the first element in the range [beg,end) for which the unary predicate op(elem) yields false.  
• All algorithms **return end if no matching elements are found**.  
• Note that op should not change its state during a function call.  
• op should not modify the passed arguments.  
• **If the range is sorted, you should use the lower_bound(), upper_bound(), equal_range(), or binary_search() algorithms**.  
• **Associative and unordered containers provide an equivalent member function, find(), which has a better complexity** (logarithmic for associative and even constant for unordered containers).  
• **Complexity: linear** (at most, numElems comparisons or calls of op(), respectively).  

```cpp
void test1()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    //查找有没有5这个元素
    // find()返回第一个满足条件的元素的迭代器
    vector<int>::iterator pos = find(v.begin(), v.end(), 5);
    if (pos != v.end())
        cout << "find the element: " << *pos << endl;
    else
        cout << "not found" << endl;
}
```

an example of finding self-defined data  

```cpp
using namespace std;
using namespace std::placeholders;

class Person
{
public:
    Person(string name, int age)
    {
        this->m_name = name;
        this->m_age = age;
    }

    bool operator==(Person p)
    {
        return this->m_name == p.m_name && this->m_age == p.m_age;
    }

    string m_name;
    int m_age;
};

class MyCmp
{
public:
    bool operator()(Person p1, Person p2) const
    {
        return p1.m_name == p2.m_name && p1.m_age == p2.m_age;
    }
};

void test()
{
    vector<Person> v {Person("a", 10), Person("b", 20), Person("c", 30), Person("d", 40)};

    // 自定义数据类型使用find函数需要重载==运算符
    vector<Person>::iterator pos = find(v.begin(), v.end(), Person("a", 10));
    if (pos != v.end())
        cout << (*pos).m_name << " " << (*pos).m_age << endl; // a 10
    else
        cout << "not found" << endl;

    // 也可以不重载==运算符，使用find_if，但需要构造仿函数和适配器
    // find_if()返回第一个满足条件的元素的迭代器
    vector<Person>::iterator pos2 = find_if(v.begin(), v.end(), bind(MyCmp(), _1, Person("a", 10)));
    if (pos2 != v.end())
        cout << (*pos2).m_name << " " << (*pos2).m_age << endl; // a 10
    else
        cout << "not found" << endl;
}
```

### Search First n Matching Consecutive Elements  

```cpp
ForwardIterator
search_n (ForwardIterator beg, ForwardIterator end, Size count, const T& value)

ForwardIterator
search_n (ForwardIterator beg, ForwardIterator end, Size count, const T& value, BinaryPredicate op)
```

• The first form returns the position of the **first of count consecutive elements in the range [beg,end) that all have a value equal to value**.  
• The second form returns the position of the first of count consecutive elements in the range [beg,end) for which the binary predicate op(elem,value) yields true (value is the passed fourth argument).  
• Both forms **return end if no matching elements are found**.  
• Note that op should not change its state during a function call.  
• op should not modify the passed arguments.  
• These algorithms were not part of the original STL and were not introduced very carefully. The fact that **the second form uses a binary predicate instead of a unary predicate breaks the consistency of the original STL**.  
• **Complexity: linear** (at most, numElems*count comparisons or calls of op(), respectively).  

Note: search_n() requires a binary predicate even if you need only a unary
predicate. The consequence is that if you have an ordinary unary predicate, such as  

```cpp
bool isPrime (int elem);
```

you either have to change the signature of your function or write a simple wrapper.  

```cpp
bool binaryIsPrime (int elem1, int) {
    return isPrime(elem1);
}
```

and also need a dummy value  

```cpp
pos = search_n (coll.begin(), coll.end(), // range
                4, // count
                0, // required dummy value
                binaryIsPrime); // binary criterion
```

```cpp
using namespace std;
using namespace std::placeholders;

bool isPrime(int num)
{
    num = abs(num);
    if (0 == num || 1 == num) return false;

    int i;
    for (i = num / 2; num % i != 0; --i);
    return i == 1;
}

bool binaryIsPrime(int num, int)
{
    return isPrime(num);
}

void test()
{
    vector<int> v {1,5,4,7,9,13,23,31,7,37,40,47,3,5};
    auto pos1 = search_n(v.begin(), v.end(), 3, 0, bind(binaryIsPrime, _1, 0));
    auto pos2 = search_n(v.begin(), v.end(), 3, 0, binaryIsPrime);

    cout << *pos1 << endl; // 13
    cout << *pos2 << endl; // 13
}
```

### Search First Subrange  

```cpp
ForwardIterator1
search (ForwardIterator1 beg, ForwardIterator1 end,
        ForwardIterator2 searchBeg, ForwardIterator2 searchEnd)

ForwardIterator1
search (ForwardIterator1 beg, ForwardIterator1 end,
        ForwardIterator2 searchBeg, ForwardIterator2 searchEnd,
        BinaryPredicate op)
```

• Both forms return the position of the first element of the **first subrange matching the range [searchBeg,searchEnd) in the range [beg,end)**.  
• In the first form, the elements of the subrange have to be equal to the elements of the whole range.  
• In the second form, for every comparison between elements, the call of the binary predicate op(elem,searchElem) has to yield true.  
• Both forms return end if no matching elements are found.  
• Note that op should not change its state during a function call.  
• op should not modify the passed arguments.  
• **Complexity: linear** (at most, numElems*numSearchElems comparisons or calls of op(), respectively).  

### Search Last Subrange  

```cpp
ForwardIterator1
find_end (ForwardIterator1 beg, ForwardIterator1 end,
          ForwardIterator2 searchBeg, ForwardIterator2 searchEnd)

ForwardIterator1
find_end (ForwardIterator1 beg, ForwardIterator1 end,
          ForwardIterator2 searchBeg, ForwardIterator2 searchEnd,
          BinaryPredicate op)
```

• Both forms return the position of the first element of the **last subrange matching the range [searchBeg,searchEnd) in the range [beg,end)**.  
• In the first form, the elements of the subrange have to be equal to the elements of the whole range.  
• In the second form, for every comparison between elements, the call of the binary predicate op(elem,searchElem) has to yield true.  
• Both forms **return end if no matching elements are found**.  
• Note that op should not change its state during a function call.  
• op should not modify the passed arguments.  
• These algorithms were not part of the original STL. Unfortunately, they were called find_end() instead of search_end(), which would be more consistent, because the algorithm used to search the first subrange is called search().  
• **Complexity: linear** (at most, numElems*numSearchElems comparisons or calls of op(), respectively).  

### Search Two Adjacent, Equal Elements  

```cpp
ForwardIterator
adjacent_find (ForwardIterator beg, ForwardIterator end)

ForwardIterator
adjacent_find (ForwardIterator beg, ForwardIterator end, BinaryPredicate op)
```

• The first form returns the first element in the range [beg,end) that has a value equal to the value of the following element.  
• The second form returns the first element in the range [beg,end) for which the binary predicate op(elem,nextElem) yields true.  
• Both forms return end if no matching elements are found.  
• Note that op should not change its state during a function call.  
• op should not modify the passed arguments.  
• **Complexity: linear** (at most, numElems comparisons or calls of op(), respectively).  

```c++
// 查找相邻重复元素
// 使用adjacent_find()，它返回第一个满足条件的元素的迭代器
vector<int> v {1,4,2,3,4,6,6,17};

vector<int>::iterator pos = adjacent_find(v.begin(), v.end());
if (pos != v.end())
    cout << *pos << endl; // 6
else
    cout << "not found" << endl;
```

## Comparing Ranges  

### Testing Equality  

```cpp
bool
equal (InputIterator1 beg, InputIterator1 end, 
       InputIterator2 cmpBeg)

bool
equal (InputIterator1 beg, InputIterator1 end, 
       InputIterator2 cmpBeg, BinaryPredicate op)
```

• The first form **returns whether the elements in the range [beg,end) are equal to the elements in the range starting with cmpBeg**.  
• The second form returns whether each call of the binary predicate op(elem,cmpElem) with the corresponding elements in the range [beg,end) and in the range starting with cmpBeg yields true.  
• Note that op should not change its state during a function call.  
• op should not modify the passed arguments.  
• **The caller must ensure that the range starting with cmpBeg contains enough elements**.  
• To determine the details of any differences, you should use the mismatch() algorithm.  
• To determine whether two sequences contain the same elements in different order, algorithm is_permutation() is provided since C++11.  
• **Complexity: linear** (at most, numElems comparisons or calls of op(), respectively).  

### Testing for Unordered Equality  

```cpp
bool
is_permutation (ForwardIterator1 beg1, ForwardIterator1 end1, ForwardIterator2 beg2)

bool
is_permutation (ForwardIterator1 beg1, ForwardIterator1 end1,
                ForwardIterator2 beg2, CompFunc op)
```

• Both forms return whether the elements in the range [beg1,end1) are a permutation of the elements in the range starting with beg2; that is, **whether they return equal elements in whatever order**.  
• The first form compares the elements by using operator ==.  
• The second form compares the elements by using the binary predicate op(elem1,elem2) which should return true when elem1 is equal to elem2.  
• Note that op should not change its state during a function call.  
• op should not modify the passed arguments.  
• All Iterators must have the same value type.  
• These algorithms are available since C++11.  
• **Complexity: at worst quadratic** (numElems1 comparisons or calls of op(), if all elements are equal and have the same order).  

## Predicates for Ranges  

### Check for (Partial) Sorting  

```cpp
bool
is_sorted (ForwardIterator beg, ForwardIterator end)

bool
is_sorted (ForwardIterator beg, ForwardIterator end, BinaryPredicate op)

ForwardIterator
is_sorted_until (ForwardIterator beg, ForwardIterator end)

ForwardIterator
is_sorted_until (ForwardIterator beg, ForwardIterator end, BinaryPredicate op)
```

• is_sorted() returns **whether the elements in the range [beg,end) are sorted**.  
• is_sorted()_until returns the position of the **first element in the range [beg,end), which breaks the sorting of this range, or end if none**.  
• The first and third forms use operator < to compare elements. The second and fourth forms use the binary predicate op(elem1,elem2) which should return true if elem1 is “less than” elem2.  
• If the range is empty or has only one element, the algorithms return true or end, respectively.  
• Note that op should not change its state during a function call.  
• op should not modify the passed arguments.  
• These algorithms are available since C++11.  
• **Complexity: linear** (at most numElems-1 calls of < or op()).  

### Check for Being a Heap (Maximum Element First)  

```cpp
bool
is_heap (RandomAccessIterator beg, RandomAccessIterator end)

bool
is_heap (RandomAccessIterator beg, RandomAccessIterator end, BinaryPredicate op)

RandomAccessIterator
is_heap_until (RandomAccessIterator beg, RandomAccessIterator end)

RandomAccessIterator
is_heap_until (RandomAccessIterator beg, RandomAccessIterator end, BinaryPredicate op)
```

• is_heap() returns **whether the elements in the range [beg,end) are a heap**, which means that beg is (one of) the maximum element(s).  
• is_heap()_until **returns the position of the first element in the range [beg,end) that breaks the sorting as a heap** (is larger than the first element) or end if none.  
• The first and third forms use operator < to compare elements. The second and fourth forms use the binary predicate op(elem1,elem2) which should return true if elem1 is “less than” elem2.  
• If the range is empty or has only one element, the algorithms return true or end, respectively.  
• Note that op should not change its state during a function call.  
• op should not modify the passed arguments.  
• These algorithms are available since C++11.  
• **Complexity: linear** (at most numElems-1 calls of < or op()).  

### All, Any, or None  

```cpp
bool
all_of (InputIterator beg, InputIterator end, UnaryPredicate op)

bool
any_of (InputIterator beg, InputIterator end, UnaryPredicate op)

bool
none_of (InputIterator beg, InputIterator end, UnaryPredicate op)
```

• These algorithms return **whether for all, any (at least one), or none of the elements in the range [beg,end), the unary predicate op(elem) yields true**.  
• **If the range is empty, all_of() and none_of() return true, whereas any_of() returns false**.  
• Note that op should not change its state during a function call.  
• op should not modify the passed arguments.  
• These algorithms are available since C++11.  
• **Complexity: linear** (at most numElems calls of op()).  

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 7.5  
https://www.bilibili.com/video/BV1hb411j7mu  
