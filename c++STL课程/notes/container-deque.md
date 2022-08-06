# deque  

## 遍历  

```c++
void printDeque(const deque<int>& d)
{
    // const_iterator 只读迭代器，配合参数const deque<int>& d使用
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}
```

## 基本操作  

```c++
deque<int> dq;
dq.push_back(1);
dq.push_back(2);
dq.push_back(3);
dq.push_front(4);
printDeque(dq);

dq.pop_back();
dq.pop_front();
printDeque(dq); // 1 2

cout << dq.front() << endl; // 1
cout << dq.back() << endl; // 2
```

```c++
// 初始化
deque<int> d1(10, 100);
printDeque(d1); //100 100 100 100 100 100 100 100 100 100

// swap
deque<int> d2(5, 10);
d2.swap(d1);
printDeque(d2); //100 100 100 100 100 100 100 100 100 100

// 插入
d1.insert(d1.begin()++, 99);
printDeque(d1); // 99 10 10 10 10 10
d1.insert(++d1.begin(), 44);
printDeque(d1); // 99 44 10 10 10 10 10

//删除
d1.erase(d1.begin());
printDeque(d1); // 44 10 10 10 10 10
d1.erase(d1.begin(), d1.end());
printDeque(d1); // 等同于d1.clear()
```

## 排序  

```c++
deque<int> q;
q.push_back(60);
q.push_back(20);
q.push_back(30);
q.push_back(10);

// 升序排序
sort(q.begin(), q.end());
printDeque(q);  // 10 20 30 60

// 降序排序
sort(q.begin(), q.end(), cmp);
printDeque(q);  // 60 30 20 10
```

```c++
// 比较器
bool cmp(int v1, int v2)
{
    return v1 > v2;
}
```
