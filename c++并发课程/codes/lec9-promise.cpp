#include <iostream>
#include <thread>
#include <future>

void mythread1(std::promise<int>& tmpp, int calc)
{
    std::chrono::milliseconds dura(2000);
    std::this_thread::sleep_for(dura);

    calc++;
    int result = calc;
    tmpp.set_value(result);

    return;
}

void mythread2(std::future<int>& tmpf)
{
    int result = tmpf.get();
    std::cout << "result is " << result << std::endl;
    return;
}

void test()
{
    std::promise<int> myprom; //声明一个std::promise对象，保存的值类型为int
    std::thread t1(mythread1, std::ref(myprom), 180);
    t1.join();

    std::future<int> f1 = myprom.get_future();
    //std::cout << f1.get() << std::endl;
    //不能使用f1.get(),否则后面std::ref(f1)会出错，因为一旦std::future.get()被调用，它将变为无效

    std::thread t2(mythread2, std::ref(f1));
    t2.join();

    return;
}

int main()
{
    test();

    return 0;
}
