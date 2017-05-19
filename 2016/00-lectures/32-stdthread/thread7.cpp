#include <thread>
#include <iostream>
#include <vector>

void func(int x, int y)
{
    std::cout << "Thread: " << x << " " << y << std::endl;
    // вызовется terminate и программа завершится
    // так как исключение нигде в нити не ловится
    if (x == 6) throw 10;
}

int main() try
{
    constexpr int N = 10;
    std::vector<std::thread> tts;
    for (int i = 0; i < N; ++i) {
        std::thread cur(func, i, N);
        tts.push_back(std::move(cur));
    }
    for (int i = 0; i < N; ++i) {
        tts[i].join();
    }
} catch (...) {
    std::cerr << "exception caught" << std::endl;
}
