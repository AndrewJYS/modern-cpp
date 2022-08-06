# 排序相关算法  

## merge  

```c++
void test1()
{
    // merge
    vector<int> v1;
    vector<int> v2;

    for (int i = 0; i < 5; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 20);
    }

    vector<int> targetV;
    targetV.resize(v1.size() + v2.size());
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), targetV.begin());
    for_each(targetV.begin(), targetV.end(), [](int val){cout << val << " ";});
    // 0 1 2 3 4 20 21 22 23 24
    cout << endl;
}
```

## sort排序  

```c++
void test2()
{
    vector<int> v1;

    for (int i = 0; i < 5; i++)
    {
        v1.push_back(i);
    }

    sort(v1.begin(), v1.end(), greater<int>());
    for_each(v1.begin(), v1.end(), [](int val){cout << val << " ";});
    // 4 3 2 1 0
    cout << endl;
}
```

## 洗牌算法  

```c++
void test3()
{
    //洗牌算法，random_shuffle()
    vector<int> v;

    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    random_shuffle(v.begin(), v.end());
    for_each(v.begin(), v.end(), [](int val){cout << val << " ";});
    // 8 1 9 2 0 5 7 3 4 6
    cout << endl;
}
```

可以用下述语句保证随机  

```c++
#include <ctime>

srand((unsigned int)time(NULL));
test3();
```

## 反转算法  

```c++
void test4()
{
    // 反转算法, reverse
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    reverse(v.begin(), v.end());
    for_each(v.begin(), v.end(), [](int val){cout << val << " ";});
    // 9 8 7 6 5 4 3 2 1 0
    cout << endl;
}
```
