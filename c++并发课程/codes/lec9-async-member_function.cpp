#include <iostream>
#include <thread>
#include <future>

class A
{
public:
    int my_func(int& param)
    {
        std::cout << "param is " << param << std::endl;
        param++;

        std::cout << "my_func() start, thread_id = " << std::this_thread::get_id() << std::endl;
        std::cout << "sleeping......" << std::endl;
        std::chrono::milliseconds dura(5000);
        std::this_thread::sleep_for(dura);

        std::cout << "my_func() ends, thread_id = " << std::this_thread::get_id() << std::endl;
        return 5;
    }
};


void test()
{
    A a;
    int param = 12;

    std::cout << "main thread, thread_id = " << std::this_thread::get_id() << std::endl;
    std::future<int> result = std::async(&A::my_func, &a, std::ref(param)); //创建一个线程并执行
    std::cout << "continue......!" << std::endl;

    //result.wait();
    std::cout << "result is " << result.get() << std::endl; //如果result.get()不返回，那么会阻塞在这儿
    std::cout << "main thread param is " << param << std::endl;
    std::cout << "end..." << std::endl; //result.get()返回后才会往下执行
    return;

    /*输出
    main thread, thread_id = 1
    continue......!
    param is 12
    my_func() start, thread_id = 1
    sleeping......
    my_func() ends, thread_id = 1
    result is 5
    main thread param is 13
    end...
    */
}

int main()
{
    test();

    return 0;
}
