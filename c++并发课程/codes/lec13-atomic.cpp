#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

void test()
{
    std::atomic<int> g_cnt {2};
    std::atomic<int> g_cnt2(g_cnt.load());
    auto g_cnt3{g_cnt.load()};

    std::cout << g_cnt2 << std::endl;
    std::cout << g_cnt3 << std::endl;

    g_cnt.store(12);
    std::cout << g_cnt << std::endl;
}

int main()
{
    test();

    return 0;
}
