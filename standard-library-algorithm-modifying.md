# momdifying algorithms  

## for_each()  

1.for_each()接受函数回调或函数对象  
2.for_each()有返回值  
3.for_each()可以绑定参数输出（使用适配器）  

```c++
using namespace std;
using namespace std::placeholders;

void myPrint(int val)
{
    cout << val << " ";
}

class MyPrint
{
public:
    void operator()(int val)
    {
        cout << val << " ";
        m_count++;
    }
    int m_count = 0;
};

class MyPrint2
{
public:
    void operator()(int val, int start) const
    {
        cout << val + start << " ";
    }
};

void test1()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    // for_each()接受函数回调或函数对象
    for_each(v.begin(), v.end(), myPrint); // 0 1 2 3 4 5 6 7 8 9
    cout << endl;

    for_each(v.begin(), v.end(), MyPrint()); // 0 1 2 3 4 5 6 7 8 9
    cout << endl;

    // for_each 有返回值
    MyPrint mp = for_each(v.begin(), v.end(), MyPrint()); // 0 1 2 3 4 5 6 7 8 9
    cout << endl;
    cout << "m_count is " << mp.m_count << endl; // m_count is 10

    // for_each可以绑定参数输出（使用适配器）
    for_each(v.begin(), v.end(), bind(MyPrint2(), _1, 1000)); // 1000 1001 1002 1003 1004 1005 1006 1007 1008 1009
    cout << endl;
}
```

## 复制元素：copy()  

```c++
void test1()
{
    // 拷贝容器
    vector<int> v;

    for (int i = 0; i < 5; i++)
    {
        v.push_back(i);
    }

    vector<int> targetV;
    targetV.resize(v.size()); //一定要预留空间

    copy(v.begin(), v.end(), targetV.begin());
    for_each(targetV.begin(), targetV.end(), [](int val){cout << val << " ";}); // 0 1 2 3 4
    cout << endl;
}
```

## 转换和结合元素：transform()  

### 转换元素  

```cpp
OutputIterator
transform (InputIterator sourceBeg, InputIterator sourceEnd,
           OutputIterator destBeg, UnaryFunc op)
```

• Calls op(elem) for each element in the source range [sourceBeg,sourceEnd) and writes each result of op to the destination range starting with destBeg.  
• Returns the position after the last transformed element in the destination range (the first element that is not overwritten with a result).  
• **The caller must ensure that the destination range is big enough or that insert iterators are used**.  
• sourceBeg and destBeg may be identical. Thus, as with for_each(), you can use this algorithm to modify elements inside a sequence.  
• To replace elements matching a criterion with a particular value, use the replace() algorithms.  
• **Complexity: linear** (numElems calls of op()).

下面这个例子中，将一个vecotr的元素加上10，再搬运到另一个vector中  

```c++
class MyTransform
{
public:
    int operator()(int val)
    {
        return val + 10;
    }
};

void test2()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    vector<int> targetV;
    targetV.resize(v.size()); // 要resize()预留空间,否则报错

    transform(v.begin(), v.end(), targetV.begin(), MyTransform());
    for_each(targetV.begin(), targetV.end(), [](int val){cout << val << " " ;}); // 10 11 12 13 14 15 16 17 18 19
    cout << endl;
}
```

### 将两序列的元素结合  

```cpp
OutputIterator
transform (InputIterator1 source1Beg, InputIterator1 source1End,
           InputIterator2 source2Beg,
           OutputIterator destBeg,
           BinaryFunc op)
```

• Calls op(source1Elem,source2Elem) for all corresponding elements from the first source range [source1Beg,source1End) and the second source range starting with source2Beg and writes each result to the destination range starting with destBeg.  
• Returns the position after the last transformed element in the destination range (the first element that is not overwritten with a result).  
• The caller must **ensure that the second source range is big enough** (has at least as many elements as the source range).  
• The caller must **ensure that the destination range is big enough or that insert iterators are used**.  
• source1Beg, source2Beg, and destBeg may be identical. Thus, you can process the results of elements that are combined with themselves, and you can overwrite the elements of a source with the results.  
• **Complexity: linear** (numElems calls of op()).  

## 赋值  

### 赋予相同的值  

```cpp
void
fill (ForwardIterator beg, ForwardIterator end, const T& newValue)

void
fill_n (OutputIterator beg, Size num, const T& newValue)
```

• fill() **assigns newValue to each element in the range [beg,end)**.  
• fill_n() **assigns newValue to the first num elements** in the range starting with beg. If num is negative, fill_n() does nothing (specified only since C++11).  
• The caller **must ensure that the destination range is big enough or that insert iterators are used**.  
• Since C++11, fill_n() returns the position after the last modified element (beg+num) or beg if num is negative (before C++11, fill_n() had return type void).  
• **Complexity: linear** (numElems, num, or 0 assignments).  

```c++
// 填充算法fill(v.begin(), v,end(), 填充值)
vector<int> v;
v.resize(5);

fill(v.begin(), v.end(), 500);
for_each(v.begin(), v.end(), [](int val){cout << val << " ";}); 
cout << endl;  // 500 500 500 500 500
```

## 替换元素  

### 替换序列内的元素  

```cpp
void
replace (ForwardIterator beg, ForwardIterator end,
         const T& oldValue, const T& newValue)

void
replace_if (ForwardIterator beg, ForwardIterator end,
            UnaryPredicate op, const T& newValue)
```

• replace() **replaces each element** in the range [beg,end) that is **equal to oldValue with newValue**.  
• **replace_if() replaces each element** in the range [beg,end) for **which the unary predicate op(elem) yields true with newValue**.  
• Note that op should not change its state during a function call.  
• **Complexity: linear** (numElems comparisons or calls of op(), respectively).  

```cpp
// 替换算法，将指定元素替换成新元素
// replace(v.begin(), v.end(), old_val, new_val);
vector<int> v {5,4,3,5,5};

replace(v.begin(), v.end(), 5, 200);
for_each(v.begin(), v.end(), [](int val){cout << val << " ";}); 
cout << endl; // 200 4 3 200 200
```

```cpp
class MyCmp
{
public:
    bool operator()(int val)
    {
        return val >= 4;
    }
};

void test()
{
    // 按条件替换算法
    // replace_if(v.begin(), v.end(), 仿函数, new_val);
    vector<int> v {5,4,3,5,5};

    replace_if(v.begin(), v.end(), MyCmp(), 200);
    for_each(v.begin(), v.end(), [](int val){cout << val << " ";}); 
    cout << endl;  // 200 200 3 200 200
}
```

### 复制并替换元素  

```cpp
OutputIterator
replace_copy (InputIterator sourceBeg, InputIterator sourceEnd,
              OutputIterator destBeg,
              const T& oldValue, const T& newValue)

OutputIterator
replace_copy_if (InputIterator sourceBeg, InputIterator sourceEnd,
                 OutputIterator destBeg,
                 UnaryPredicate op, const T& newValue)
```

• replace_copy() is a **combination of copy() and replace()**. It replaces each element in the source range [sourceBeg,sourceEnd) that is equal to oldValue with newValue while the elements are copied into the destination range starting with destBeg.  
• replace_copy_if() is a combination of copy() and replace_if(). It replaces each element in the source range [sourceBeg,sourceEnd) for which the unary predicate op(elem) yields true with newValue while the elements are copied into the destination range starting with destBeg.  
• Both algorithms return the position after the last copied element in the destination range (the first element that is not overwritten).  
• Note that op should not change its state during a function call.  
• The caller must **ensure that the destination range is big enough or that insert iterators are used**.  
• **Complexity: linear** (numElems comparisons or calls of op() and assignments, respectively).  

## references  

The C++ Standard Library, A Tutorial and Reference, 2nd edition, Chapter 11.4, 11.6  
https://www.bilibili.com/video/BV1hb411j7mu  
