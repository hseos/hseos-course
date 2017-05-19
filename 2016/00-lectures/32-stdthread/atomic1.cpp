#include <thread>
#include <iostream>
#include <atomic>

//std::atomic<int> counter;
std::atomic_int counter;

void func()
{
    for (int i = 0; i < 1000000; ++i) {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main()
{
    std::thread thr1{func};
    std::thread thr2{func};

    thr1.join();
    thr2.join();
    std::cout << counter << std::endl;
}
