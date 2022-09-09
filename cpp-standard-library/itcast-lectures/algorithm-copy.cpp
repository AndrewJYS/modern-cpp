#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

void test1()
{
    // 拷贝容器
    vector<int> v;

    for (int i = 0; i < 5; i++)
    {
        v.push_back(i);
    }

    vector<int> targetV;
    targetV.resize(v.size());
    copy(v.begin(), v.end(), targetV.begin());
    for_each(targetV.begin(), targetV.end(), [](int val){cout << val << " ";}); // 0 1 2 3 4
    cout << endl;
}

void test2()
{
    // 替换算法，将指定元素替换成新元素
    // replace(v.begin(), v.end(), old_val, new_val);
    vector<int> v;

    v.push_back(5);
    v.push_back(4);
    v.push_back(3);
    v.push_back(5);
    v.push_back(5);

    replace(v.begin(), v.end(), 5, 200);
    for_each(v.begin(), v.end(), [](int val){cout << val << " ";}); // 200 4 3 200 200
    cout << endl;
}

class MyCmp3
{
public:
    bool operator()(int val)
    {
        return val >= 4;
    }
};

void test3()
{
    // 按条件替换算法
    // replace_if(v.begin(), v.end(), 仿函数, new_val);
    vector<int> v;

    v.push_back(5);
    v.push_back(4);
    v.push_back(3);
    v.push_back(5);
    v.push_back(5);

    replace_if(v.begin(), v.end(), MyCmp3(), 200);
    for_each(v.begin(), v.end(), [](int val){cout << val << " ";}); // 200 200 3 200 200
    cout << endl;
}

void test4()
{
    // swap()
    vector<int> v1;

    for (int i = 0; i < 5; i++)
    {
        v1.push_back(i);
    }

    vector<int> v2(10, 10);

    swap(v1, v2);
    for_each(v1.begin(), v1.end(), [](int val){cout << val << " ";});
    // 10 10 10 10 10 10 10 10 10 10
    cout << endl;
}

int main()
{
    test1();
    test2();
    test3();
    test4();

    return 0;
}
