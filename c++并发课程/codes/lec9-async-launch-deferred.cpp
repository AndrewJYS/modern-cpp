#include <iostream>
#include <future>
#include <thread>

void my_thread()
{
    std::cout << "sub-thread begins, id =  " << std::this_thread::get_id() << std::endl;
    std::cout << "sub-thread ends, id =  " << std::this_thread::get_id() << std::endl;
}

void test()
{
    std::future<void> result = std::async(std::launch::deferred, my_thread);
    //注意没有result.wait();
    return;
}

int main()
{
    test();

    return 0;
}
