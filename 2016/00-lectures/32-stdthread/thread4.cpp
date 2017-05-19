#include <thread>
#include <iostream>
#include <array>

void func(int x, int y)
{
    std::cout << "Thread: " << x << " " << y << std::endl;
}

int main()
{
    constexpr int N = 10;
    std::array<std::thread, N> tts;
    for (int i = 0; i < N; ++i) {
        // присваивание с переносом для std::array
        tts[i] = std::thread(func, i, N);
    }
    for (int i = 0; i < N; ++i) {
        tts[i].join();
    }
}
