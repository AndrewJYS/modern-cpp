# removing algorithm  

**These algorithms, however, cannot change the number of elements. The algorithms move logically only by overwriting “removed” elements with the following elements that were not removed. They return the new logical end of the range** (the position after the last element not removed).  

## Removing Certain Values  

### Removing Elements in a Sequence  

```cpp
ForwardIterator
remove (ForwardIterator beg, ForwardIterator end, const T& value)

ForwardIterator
remove_if (ForwardIterator beg, ForwardIterator end, UnaryPredicate op)
```

• remove() removes each element in the range [beg,end) that is equal to value.  
• remove_if() removes each element in the range [beg,end) for which the unary predicate op(elem) yields true.  
• Both algorithms return the logical new end of the modified sequence (the position after the last element not removed).  
• **The algorithms overwrite “removed” elements by the following elements that were not removed**.  
• **The order of elements that were not removed remains stable**.  
• It is up to the caller, after calling this algorithm, to use the **returned new logical end** instead of the original end end.  
• Note that op should not change its state during a function call.  
• Note that **remove_if() usually copies the unary predicate inside the algorithm and uses it twice. This may lead to problems if the predicate changes its state due to the function call**.（**目前STL只有remove_if()这个函数有问题，因此，使用它的时候，谓词要声明const**，见原书485页）  
• Due to modifications, you can’t use these algorithms for an associative or unordered container. However, these containers provide a similar member function, erase().  
• Lists provide an equivalent member function, remove(), which offers better performance because it relinks pointers instead of assigning element values.  
• **Complexity: linear** (numElems comparisons or calls of op(), respectively).  

### 复制时一并移除元素  

```cpp
OutputIterator
remove_copy (InputIterator sourceBeg, InputIterator sourceEnd,
            OutputIterator destBeg,
            const T& value)

OutputIterator
remove_copy_if (InputIterator sourceBeg, InputIterator sourceEnd,
                OutputIterator destBeg,
                UnaryPredicate op)
```

• remove_copy() is a combination of copy() and remove(). It copies each element in the source range [sourceBeg,sourceEnd) that is not equal to value into the destination range starting with destBeg.  
• remove_copy_if() is a combination of copy() and remove_if(). It copies each element in the source range [sourceBeg,sourceEnd) for which the unary predicate op(elem) yields false into the destination range starting with destBeg.  
• Both algorithms return the position after the last copied element in the destination range (the first element that is not overwritten).  
• Note that op should not change its state during a function call.  
• The caller must ensure that the destination range is big enough or that insert iterators are used.  
• Use partition_copy() (原书594页), to copy elements into two destination ranges: one fulfilling and one non fulfilling a predicate (available since C++11).  
• **Complexity: linear** (numElems comparisons or calls of op() and assignments, respectively).  

## 移除重复元素  

### 移除连续重复元素  

```cpp
ForwardIterator
unique (ForwardIterator beg, ForwardIterator end)

ForwardIterator
unique (ForwardIterator beg, ForwardIterator end, BinaryPredicate op)
```

• Both forms collapse **consecutive** equal elements by removing the following duplicates.  
• The first form removes from the range [beg,end) all elements that are equal to the previous elements. Thus, only when the elements in the sequence are sorted, or at least when all elements of the same value are adjacent, does it remove all duplicates.  
• The second form removes all elements that follow an element e and for which the binary predicate op(e,elem) yields true. In other words, **the predicate is not used to compare an element with its predecessor; the element is compared with the previous element that was not removed**.  
• Both forms return the logical new end of the modified sequence (the position after the last element not removed).  
• **The algorithms overwrite “removed” elements by the following elements that were not removed**.  
• **The order of elements that were not removed remains stable**.  
• It is up to the caller, after calling this algorithm, to use the **returned new logical end** instead of the original end end.  
• Note that op should not change its state during a function call.  
• Due to modifications, you **can’t use these algorithms for an associative or unordered container**.  
• Lists provide an equivalent member function, unique(), which offers better performance because it relinks pointers instead of assigning element values.  
• **Complexity: linear** (numElems comparisons or calls of op(), respectively).  

```cpp
using namespace std;
using namespace std::placeholders;

class cmp
{
public:
    bool operator()(int a, int b)
    {
        return (a + b) > 9;
    }
};

void test()
{
    vector<int> v{1,4,6,8,10,5,3,7,8,6};
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;  // 1 4 6 8 10 5 3 7 8 6

    auto pos = unique(v.begin(), v.end(), bind(cmp(), _1, _2));
    v.erase(pos, v.end());
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;  // 1 4 5 3 6
}
```

### 复制过程中移除连续重复元素  

```cpp
OutputIterator
unique_copy (InputIterator sourceBeg, InputIterator sourceEnd,
            OutputIterator destBeg)

OutputIterator
unique_copy (InputIterator sourceBeg, InputIterator sourceEnd,
            OutputIterator destBeg,
            BinaryPredicate op)
```

• Both forms are a combination of copy() and unique().  
• They copy all elements of the source range [sourceBeg,sourceEnd) that are no duplicates of their previous elements into the destination range starting with destBeg.  
• Both forms return the position after the last copied element in the destination range (the first element that is not overwritten).  
• The caller must ensure that the destination range is big enough or that insert iterators are used.  
• Complexity: linear (numElems comparisons or calls of op() and assignments, respectively).  

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 11.7  
https://www.bilibili.com/video/BV1hb411j7mu  
