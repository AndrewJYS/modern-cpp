# set  

set中的迭代器是const迭代器，也就是说，不能通过set的迭代器修改对应的值  

## 遍历  

```c++
void printSet(const set<int>& S)
{
    for (set<int>::const_iterator it = S.begin(); it != S.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}
```

## 基本操作  

```c++
set<int> s;
s.insert(1);
s.insert(6);
s.insert(5);
s.insert(8);


// 插入
pair<set<int>::iterator, bool> it = s.insert(8);
if (it.second)
    cout << "insert successfully" << endl;
else
    cout << "fail to insert" << endl;  // 输出fail to insert


// 查找，如果找到则返回该元素的迭代器，否则返回end()
set<int>::iterator pos = s.find(3);
// 下述例子输出 not found
if (pos != s.end())
    cout << "find the element" << endl;
else
    cout << "not found" << endl;


// 计数，count()返回0或1
cout << s.count(8) << endl; // 1
cout << s.count(3) << endl; // 0


// lower_bound(keyElem), 返回第一个 >= keyElem的元素的迭代器，找不到则返回end()
set<int>::iterator low = s.lower_bound(0);
// 下述例子输出 lower bound is 1
if (low != s.end())
    cout << "lower bound is " << *low << endl;
else
    cout << "lower bound not found" << endl;


// upper_bound(keyElem), 返回第一个 > keyElem的元素的迭代器，找不到则返回end()
set<int>::iterator upp = s.upper_bound(8);
// 下述例子输出 lower bound not found
if (upp != s.end())
    cout << "upper bound is " << *upp << endl;
else
    cout << "upper bound not found" << endl;


// equal_range(keyElem) 返回pair<lower_bound(keyElem), upper_bound(keyElem)>
pair<set<int>::iterator, set<int>::iterator> it = s.equal_range(6);
if (it.first != s.end())
    cout << "lower bound is " << *(it.first) << endl;
else
    cout << "lower bound not found" << endl;
if (it.second != s.end())
    cout << "upper bound is " << *(it.second) << endl;
else
    cout << "upper bound not found" << endl;
```

## 仿函数改变set的排序规则  

```c++
set<int> s; // set是自带从小到大排序的  
s.insert(1);
s.insert(6);
s.insert(5);
s.insert(4);
s.insert(8);
printSet(s); // 1 4 5 6 8

s.erase(6);
printSet(s);  // 1 4 5 8

// 插入之前指定从大到小排序
set<int, MyCMP> newS;
newS.insert(1);
newS.insert(6);
newS.insert(5);
newS.insert(4);
newS.insert(8);

for (set<int, MyCMP>::iterator it = newS.begin(); it != newS.end(); it++)
{
    cout << *it << " "; // 8 6 5 4 1
}
cout << endl;
```

```c++
// 仿函数（这里不能使用比较器，否则不匹配，会报错）

class MyCMP
{
public:
    bool operator()(int v1, int v2)
    {
        return v1 > v2;
    }
};
```
