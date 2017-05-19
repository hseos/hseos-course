#include <thread>
#include <iostream>

void func(int x, int y)
{
    std::cout << "Thread: " << x << " " << y << std::endl;
}

int main()
{
    constexpr int N = 10;
    std::thread tts[N];
    for (int i = 0; i < N; ++i) {
        // присваивание с переносом для std::thread
        tts[i] = std::thread(func, i, N);
    }
    for (int i = 0; i < N; ++i) {
        tts[i].join();
    }
}
