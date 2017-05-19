#include <thread>
#include <mutex>
#include <iostream>

volatile int counter;
std::mutex m;
std::recursive_mutex m2;

void func()
{
    for (int i = 0; i < 1000000; ++i) {
        // RAII для захвата сразу нескольких mutex
        // с гарантией от deadlock
        std::scoped_lock g{m, m2};
        ++counter;
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
