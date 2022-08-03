#include <iostream>
#include <thread>

void do_something(int i){}

struct func
{
    int& i;
    func(int& i_): i(i_) {}
    void operator()()
    {
        for (int j = 0; j < 1000000; ++j)
        {
            if (j % 100000 == 0)
                std::cout << j << std::endl;
            do_something(i);
        }
    }
};

void oops()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
}

int main()
{
    oops();

    return 0;
}
