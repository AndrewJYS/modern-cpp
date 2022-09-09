# 其他算法  

## 已排序区间算法  

### 查找元素  

```cpp
bool
binary_search (ForwardIterator beg, ForwardIterator end, const T& value)

bool
binary_search (ForwardIterator beg, ForwardIterator end, const T& value, BinaryPredicate op)
```

• Both forms return whether **the sorted range** [beg,end) contains an element equal to value.  
• op is an optional binary predicate to be used as the sorting criterion: op(elem1,elem2).  
• To obtain the position of an element for which you are searching, use lower_bound(), upper_bound(), or equal_range().  
• The caller has to ensure that the ranges are sorted according to the sorting criterion on entry.  
• Complexity: logarithmic for random-access iterators, linear otherwise (at most, log(numElems) + 2 comparisons; but for other than random-access iterators, the number of operations to step through the elements is linear, making the total complexity linear).  

```cpp
// 二分查找排序数组中的元素
vector<int> v {1,2,5,8,13};

bool res = binary_search(v.begin(), v.end(), 5);
cout << res << endl; // 1
```

### 合并两个已排序的集合  

```cpp
OutputIterator
merge (InputIterator source1Beg, InputIterator source1End,
        InputIterator source2Beg, InputIterator source2End,
        OutputIterator destBeg)

OutputIterator
merge (InputIterator source1Beg, InputIterator source1End,
        InputIterator source2Beg, InputIterator source2End,
        OutputIterator destBeg, BinaryPredicate op)
```

```cpp
vector<int> v1 {1,2,4,6,8};
vector<int> v2 {3,5,6,9,10};
vector<int> v3;
v3.resize(v1.size() + v2.size());
vector<int> v4;
v4.resize(v1.size() + v2.size());

merge(v1.begin(), v1.end(),
        v2.begin(), v2.end(),
        v3.begin());
for_each(v3.cbegin(), v3.cend(), [](int val){ cout << val << " "; });
cout << endl; // 1 2 3 4 5 6 6 8 9 10
```

### 已排序集合的交集  

```cpp
OutputIterator
set_intersection (InputIterator source1Beg, InputIterator source1End,
                    InputIterator source2Beg, InputIterator source2End,
                    OutputIterator destBeg)

OutputIterator
set_intersection (InputIterator source1Beg, InputIterator source1End,
                    InputIterator source2Beg, InputIterator source2End,
                    OutputIterator destBeg, BinaryPredicate op)
```

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; 

void test1()
{
    // 集合的交集,set_intersection()
    // set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), targetV.begin());
    // 返回targetV[交集.size()]迭代器，具体见示例
    vector<int> v1;
    vector<int> v2;

    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 5);
    }


    vector<int> targetV;
    targetV.resize(min(v1.size(), v2.size()));
    vector<int>::iterator pos = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), targetV.begin());
    cout << *pos << endl; // 0

    for_each(targetV.begin(), pos, [](int val){cout << val << " ";}); // 5 6 7 8 9
    cout << endl;
}
```

### 已排序集合的并集  

```cpp
OutputIterator
set_union (InputIterator source1Beg, InputIterator source1End,
            InputIterator source2Beg, InputIterator source2End,
            OutputIterator destBeg)

OutputIterator
set_union (InputIterator source1Beg, InputIterator source1End,
            InputIterator source2Beg, InputIterator source2End,
            OutputIterator destBeg, BinaryPredicate op)
```

```cpp
void test2()
{
    // 集合的并集,set_union()
    // set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), targetV.begin());
    vector<int> v1;
    vector<int> v2;

    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 5);
    }


    vector<int> targetV;
    targetV.resize(v1.size() + v2.size());
    vector<int>::iterator pos = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), targetV.begin());

    for_each(targetV.begin(), pos, [](int val){cout << val << " ";});
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
    cout << endl;
}
```

### 已排序集合的差集  

```cpp
OutputIterator
set_difference (InputIterator source1Beg, InputIterator source1End,
                InputIterator source2Beg, InputIterator source2End,
                OutputIterator destBeg)

OutputIterator
set_difference (InputIterator source1Beg, InputIterator source1End,
                InputIterator source2Beg, InputIterator source2End,
                OutputIterator destBeg, BinaryPredicate op)
```

```cpp
void test3()
{
    // 集合的并差集,set_difference()
    // set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), targetV.begin());
    vector<int> v1;
    vector<int> v2;

    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 5);
    }


    vector<int> targetV;
    targetV.resize(max(v1.size(), v2.size()));
    vector<int>::iterator pos = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), targetV.begin());

    for_each(targetV.begin(), pos, [](int val){cout << val << " ";}); // 0 1 2 3 4
    cout << endl;
}
```

## 数值算法  

### accumulate  

```cpp
T
accumulate (InputIterator beg, InputIterator end, T initValue)

T
accumulate (InputIterator beg, InputIterator end, T initValue, BinaryFunc op)
```

• The first form computes and returns the sum of initValue and all elements in the range [beg,end). In particular, **it calls the following for each element: initValue = initValue + elem**  
• The second form computes and returns the result of calling op for initValue and all elements in the range [beg,end). In particular, it calls the following for each element: **initValue = op(initValue,elem)**  
• Thus, for the values a1 a2 a3 a4 ... they compute and return either initValue + a1 + a2 + a3 + ... or initValue op a1 op a2 op a3 op ... respectively.  
• If the range is empty (beg==end), both forms return initValue.  
• op must not modify the passed arguments.  
• **Complexity: linear** (numElems calls of operator + or op(), respectively).  

注意：accumulate()算法的头文件是numeric  

```c++
#include <numeric>

void test1()
{
    // 累加算法
    // accumulate(v.begin(), v.end(), 累加值/起始累加值)
    vector<int> v;

    for (int i = 1; i < 101; i++)
    {
        v.push_back(i);
    }

    int num1 = accumulate(v.begin(), v.end(), 0);
    cout << num1 << endl; // 5050
    int num2 = accumulate(v.begin(), v.end(), 10);
    cout << num2 << endl; // 5060
}
```

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 11.10, 11.11  
https://www.bilibili.com/video/BV1hb411j7mu  
