#include <thread>
#include <mutex>
#include <iostream>

volatile int counter;
std::mutex m;

void func()
{
    for (int i = 0; i < 1000000; ++i) {
        // RAII для std::mutex
        // конструктор для gr захватывает mutex
        // а деструктор освобождает
        std::lock_guard gr{m};
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
