# mutating algorithms  

## 反转元素次序  

```cpp
void
reverse (BidirectionalIterator beg, BidirectionalIterator end)

OutputIterator
reverse_copy (BidirectionalIterator sourceBeg, BidirectionalIterator sourceEnd, OutputIterator destBeg)
```

• reverse() **reverses the order** of the elements inside the range [beg,end).  
• reverse_copy() reverses the order of the elements while copying them from the source range [sourceBeg,sourceEnd) to the destination range starting with destBeg.  
• reverse_copy() returns the position after the last copied element in the destination range (the first element that is not overwritten).  
• The caller **must ensure that the destination range is big enough or that insert iterators are used**.  
• **Lists provide an equivalent member function, reverse(), which offers better performance because it relinks pointers instead of assigning element values**.  
• **Complexity: linear** (numElems/2 swaps or numElems assignments, respectively).  

```c++
// 反转算法, reverse
vector<int> v;
for (int i = 0; i < 10; i++)
{
    v.push_back(i);
}

reverse(v.begin(), v.end());
for_each(v.begin(), v.end(), [](int val){cout << val << " ";});
cout << endl;  // 9 8 7 6 5 4 3 2 1 0
```

## 旋转元素  

```cpp
ForwardIterator
rotate (ForwardIterator beg, ForwardIterator newBeg, ForwardIterator end)
```

• Rotates elements in the range [beg,end) so that ***newBeg is the new first element** after the call.  
• Since C++11, returns beg+(end-newbeg), which is the new position of the first element. Before C++11, the return type was void.  
• The caller must **ensure that newBeg is a valid position in the range [beg,end)**; otherwise, the call results in undefined behavior.  
• **Complexity: linear** (at most, numElems swaps).  

```cpp
OutputIterator
rotate_copy (ForwardIterator sourceBeg, ForwardIterator newBeg, ForwardIterator sourceEnd,
            OutputIterator destBeg)
```

• Is a combination of **copy() and rotate()**.  
• Copies the elements of the source range [sourceBeg,sourceEnd) into the destination range starting with destBeg in rotated order so that ***newBeg is the new first element**.  
• Returns destBeg+(sourceEnd-sourceBeg), which is the position after the last copied element in the destination range.  
• The caller must **ensure that newBeg is an element in the range [beg,end)**; otherwise, the call results in undefined behavior.  
• The caller must **ensure that the destination range is big enough** or that insert iterators are used.  
• The source and destination ranges should not overlap.  
• **Complexity: linear** (numElems assignments).  

```cpp
vector<int> v1 {1,2,3,4,5,6,7,8,9};
auto pos = v1.begin() + 2;
rotate(v1.begin(), pos, v1.end());
for_each(v1.cbegin(), v1.cend(), [](int val){ cout << val << " "; });
cout << endl;  // 3 4 5 6 7 8 9 1 2

vector<int> v2;
v2.resize(v1.size());
rotate_copy(v1.begin(), v1.begin()+3, v1.end()-2, v2.begin());
for_each(v2.cbegin(), v2.cend(), [](int val){ cout << val << " "; });
cout << endl;  // 6 7 8 9 3 4 5 0 0
```

## 对元素重新洗牌  

```cpp
void
shuffle (RandomAccessIterator beg, RandomAccessIterator end, UniformRandomNumberGenerator&& eng)

void
random_shuffle (RandomAccessIterator beg, RandomAccessIterator end)

void
random_shuffle (RandomAccessIterator beg, RandomAccessIterator end, RandomFunc&& op)
```

• The first form, available since C++11, shuffles the order of the elements in the range [beg,end), using an engine eng as introduced by the random numbers and distributions library.  
• The second form shuffles the order of the elements in the range [beg,end), using an implementation- defined uniform distribution random-number generator, such as the C function rand().  
• The third form shuffles the order of the elements in the range [beg,end), using op. op is called with an integral value of difference_type of the iterator: op(max) which should return a random number greater than or equal to zero and less than max. Thus, it should not return max itself.  
• For shuffle(), you should not pass an engine just temporarily created.  
• Before C++11, op was declared as RandomFunc&, so you couldn’t pass a temporary value or an ordinary function.  
• **Complexity: linear** (numElems-1 swaps).  

```cpp
//可以用下述语句保证随机
srand((unsigned int)time(NULL));

//洗牌算法，random_shuffle()
vector<int> v {0,1,2,3,4,5,6,7,8,9};

random_shuffle(v.begin(), v.end());
for_each(v.begin(), v.end(), [](int val){cout << val << " ";});
cout << endl;  // 8 1 9 2 0 5 7 3 4 6
```

## 将元素向前搬  

```cpp
ForwardIterator
partition (ForwardIterator beg, ForwardIterator end, UnaryPredicate op)

BidirectionalIterator
stable_partition (BidirectionalIterator beg, BidirectionalIterator end, UnaryPredicate op)
```

• Both algorithms **move all elements in the range [beg,end) to the front, for which the unary predicate op(elem) yields true**.  
• Both algorithms return the first position for which op() yields false.  
• The difference between partition() and stable_partition() is that the algorithm **stable_partition() preserves the relative order of elements** that match the criterion and those that do not.  
• You could use this algorithm to split elements into two parts according to a sorting criterion. The nth_element() algorithm has a similar ability.  
• Note that op should not change its state during a function call.  
• Before C++11, partition() required bidirectional iterators instead of forward iterators and guaranteed at most numElems/2 swaps.  
• Use partition_copy() to copy elements into one destination range for fulfilling and one for not fulfilling a predicate (available since C++11).  
• Complexity:  
– For **partition(): linear** (at most numElems/2 swaps and numElems calls of op() if bidirectional iterators or random-access iterators are used; at most numElems swaps if the iterators are only forward iterators).  
– For **stable_partition(): linear if there is enough extra memory** (numElems swaps and calls of op()); otherwise, n-log-n (numElems calls of op() but numElems*log(numElems) swaps).  

```cpp
pair<OutputIterator1,OutputIterator2>
partition_copy (InputIterator sourceBeg, InputIterator sourceEnd,
                OutputIterator1 destTrueBeg, OutputIterator2 destFalseBeg,
                UnaryPredicate op)
```

• Splits all elements in the range [beg,end) according to the predicate op() into two subranges.  
• All elements for which the unary predicate op(elem) yields true are copied into the range starting with destTrueBeg. All elements for which the predicate yields false are copied into the range starting with destFalseBeg.  
• The algorithm returns a pair of the position after the last copied elements of the destination ranges (the first element that is not overwritten).  
• Note that op should not change its state during a function call.  
• This algorithm is available since C++11.  
• Use copy_if() (see Section 11.6.1, page 557) or remove_copy_if() if you need only the elements that either fulfill or do not fulfill the predicate.  
• Complexity: linear (at most numElems applications of op()).  

```cpp
class Even
{
public:
    bool operator()(int val)
    {
        return val % 2 == 0;
    }
};

void print(int val)
{
    cout << val << " ";
}

void test1()
{
    vector<int> v1 {3,5,4,7,2,9,8,6,1,10};
    vector<int> v2(v1);

    partition(v1.begin(), v1.end(), Even());
    for_each(v1.cbegin(), v1.cend(), print);
    cout << endl; // 10 6 4 8 2 9 7 5 1 3

    stable_partition(v2.begin(), v2.end(), Even());
    for_each(v2.cbegin(), v2.cend(), print);
    cout << endl; // 4 2 8 6 10 3 5 7 9 1
}

void test2()
{
    vector<int> v1 {3,5,4,7,2,9,8,6,1,10};
    vector<int> oddcoll;
    vector<int> evencoll;

    partition_copy(v1.begin(), v1.end(),
                   back_inserter(evencoll), back_inserter(oddcoll),
                   Even());
    for_each(oddcoll.cbegin(), oddcoll.cend(), print);  cout << endl;  // 3 5 7 9 1
    for_each(evencoll.cbegin(), evencoll.cend(), print);  cout << endl; // 4 2 8 6 10
}
```

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 11.8  
https://www.bilibili.com/video/BV1hb411j7mu  
