#include <iostream>
#include <memory>
using namespace std;

class Test
{
public:
    ~Test()
    {
        cout << "析构函数" << endl;
    }
};

void test_unique_ptr()
{
    unique_ptr<int> up1(new int(11)); //创建智能指针对象
    cout << *up1 << endl; //unique_ptr重载了operator*()
    up1 = nullptr; // 也可以人为指定释放堆区空间,NULL和reset()也可以，如下
    up1 = NULL;
    up1.reset(); // 多次释放也没有问题


    {
        unique_ptr<Test> up2(new Test); //会输出 ”析构函数“
        // 说明到作用域外，会自动销毁
    }


    unique_ptr<int> up3(new int(10));
    // unique_ptr<int> up4 = up3; // error, forbid copy constructor
    unique_ptr<int> up4 = std::move(up3); // 把up3的使用权转交给up4，up3不能被使用
    cout << *up4 << endl; // 10
    // cout << *up3 << endl; // error


    // up4.reset()如果没有参数，作用是显式释放堆区内容
    up4.reset(new int(22)); // 如果有参数，先释放原来堆区内容，重新给up1绑定一个新的堆区内容
    cout << *up4 << endl; // 22


    unique_ptr<int> up5(new int(15));
    int* p = up5.release(); // 释放控制权，不释放堆区内存
    cout << *p << endl; // 15
    // cout << *up5 << endl;  // error
    delete p;
}

void test_shared_ptr()
{
    shared_ptr<int> sp1(new int(11));
    shared_ptr<int> sp2 = sp1; // 拷贝构造函数
    cout << *sp2 << endl; // 1
    cout << sp2.use_count() << endl; //打印引用计数, 2
    cout << sp1.use_count() << endl; //打印引用计数, 2

    sp1.reset(); // 释放
    cout << *sp2 << endl; // 11
    // cout << *sp1 << endl; // error,sp1已经释放
    cout << sp1.use_count() << endl; // 0，因为sp1释放了，所以它的引用计数为0
    cout << sp2.use_count() << endl; // 1，因为sp1释放了，sp2的引用计数会减一
    sp2.reset(); // 再次释放
}

void test_weak_ptr()
{
    shared_ptr<int> p1(new int(11));
    shared_ptr<int> p2 = p1;
    weak_ptr<int> wp1 = p1;
    cout << p1.use_count() << " " << p2.use_count() << " " << wp1.use_count() << endl; // 2 2 2

    // weak_ptr虽然不和堆区空间绑定，但可以通过lock函数获取shared_ptr<int>对象
    shared_ptr<int> p3 = wp1.lock();
    cout << p1.use_count() << " " << p2.use_count() << " " << p3.use_count() << " " << wp1.use_count() << endl; // 3 3 3 3

    cout << *p1 << " " << *p2 << " " << *p3 << endl; // 11 11 11
    // cout << *wp1 << endl; // error，没有重载*

    p1.reset();
    p2.reset();
    p3.reset();
    cout << p1.use_count() << " " << p2.use_count() << " " << p3.use_count() << endl; // 0 0 0

    // 当堆区空间释放了，wp1.lock()返回为nullptr
    shared_ptr<int> tmp = wp1.lock();
    if (tmp == nullptr) cout << "堆区空间释放" << endl;
}

int main()
{
    //test_shared_ptr();
    test_weak_ptr();

    return 0;
}
