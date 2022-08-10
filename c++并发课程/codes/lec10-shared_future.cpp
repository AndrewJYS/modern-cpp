#include <iostream>
#include <thread>
#include <future>

int my_func()
{
    return 5;
}

void test()
{
    std::future<int> result = std::async(std::launch::async, my_func); //创建一个线程并执行
    std::shared_future<int> shared_result1(std::move(result)); //此时result为空
    std::cout << shared_result1.get() << std::endl; // 5
    std::cout << shared_result1.get() << std::endl; // 5


    std::shared_future<int> shared_result2 = std::async(std::launch::async, my_func);
    std::cout << shared_result2.get() << std::endl;
    std::cout << shared_result2.get() << std::endl;
}

int main()
{
    test();

    return 0;
}
