# 排序算法  

## 对所有元素排序  

```cpp
void
sort (RandomAccessIterator beg, RandomAccessIterator end)

void
sort (RandomAccessIterator beg, RandomAccessIterator end, BinaryPredicate op)

void
stable_sort (RandomAccessIterator beg, RandomAccessIterator end)

void
stable_sort (RandomAccessIterator beg, RandomAccessIterator end, BinaryPredicate op)
```

• The **first forms of sort() and stable_sort()** sort all elements in the range [beg,end) **with operator <**.  
• The **second forms of sort() and stable_sort()** sort all elements by **using the binary predicate op(elem1,elem2)** as the sorting criterion. It should return true if elem1 is “less than” elem2.  
• Note that op has to define a strict weak ordering for the values.  
• Note that op should not change its state during a function call.  
• The difference between sort() and stable_sort() is that stable_sort() guarantees that the order of equal elements remains stable.  
• You can’t call these algorithms for lists or forward lists, because both do not provide randomaccess iterators. However, they provide a special member function to sort elements: sort().  
• sort() guarantees a good performance (n-log-n) on average. However, if avoiding worst-case performance is important, you should use partial_sort() or stable_sort().  
• Complexity:  
– For **sort(): n-log-n** on average (approximately numElems*log(numElems) comparisons on average).  
– For **stable_sort(): n-log-n if there is enough extra memory** (numElems*log(numElems) comparisons); **otherwise, n-log-n*log-n** (numElems\*log(numElems)^2 comparisons).  

```cpp
vector<int> v1 {0,1,2,3,4};

sort(v1.begin(), v1.end(), greater<int>());
for_each(v1.begin(), v1.end(), [](int val){cout << val << " ";});
cout << endl;  // 4 3 2 1 0
```

## 根据第n个元素排序  

```cpp
void
nth_element (RandomAccessIterator beg, RandomAccessIterator nth, RandomAccessIterator end)

void
nth_element (RandomAccessIterator beg, RandomAccessIterator nth, RandomAccessIterator end, BinaryPredicate op)
```

• Both forms sort the elements in the range [beg,end), so the correct element is at the nth position, and **all elements in front are less than or equal to this element, and all elements that follow are greater than or equal to it**. Thus, you get two subsequences separated by the element at position n, whereby each element of the first subsequence is less than or equal to each element of the second subsequence. This is helpful if you need only the set of the n highest or lowest elements without having all the elements sorted.  
• The first form uses operator < as the sorting criterion.  
• The second form uses the binary predicate op(elem1,elem2) as the sorting criterion.  
• Note that op has to define a strict weak ordering for the values.  
• Note that op should not change its state during a function call.  
• The partition() algorithm is also provided to split elements of a sequence into two parts according to a sorting criterion.  
• **Complexity: linear** on average.  

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 11.9  
https://www.bilibili.com/video/BV1hb411j7mu  
