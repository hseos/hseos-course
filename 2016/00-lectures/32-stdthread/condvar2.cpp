#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <chrono>
#include <array>

std::condition_variable c;
std::mutex m;
int count;

void func()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::scoped_lock l{m};
    if (++count == 5)
        c.notify_one();
}

int main()
{
    constexpr auto N = 10;
    std::array<std::thread, N> ts;
    for (int i = 0; i < N; ++i) {
        ts[i] = std::thread(func);
    }
    {
        std::unique_lock l{m};
        c.wait(l);
        std::cout << "ready 5" << std::endl;
    }
    for (int i = 0; i < N; ++i) {
        ts[i].join();
    }
}
