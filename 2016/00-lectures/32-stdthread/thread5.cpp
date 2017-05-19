#include <thread>
#include <iostream>
#include <vector>

void func(int x, int y)
{
    std::cout << "Thread: " << x << " " << y << std::endl;
}

int main()
{
    constexpr int N = 10;
    std::vector<std::thread> tts;
    for (int i = 0; i < N; ++i) {
        // создаем нить и добавляем в вектор
        tts.emplace_back(func, i, N);
    }
    for (int i = 0; i < N; ++i) {
        tts[i].join();
    }
}
