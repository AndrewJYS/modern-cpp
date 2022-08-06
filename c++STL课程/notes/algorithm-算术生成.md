# 算术生成算法  

## 累加算法  

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

## 填充算法  

```c++
void test2()
{
    // 填充算法fill(v.begin(), v,end(), 填充值)
    vector<int> v;
    v.resize(5);

    fill(v.begin(), v.end(), 500);
    for_each(v.begin(), v.end(), [](int val){cout << val << " ";}); // 500 500 500 500 500
    cout << endl;
}
```
