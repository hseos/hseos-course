#include <future>
#include <thread>
#include <iostream>

int main()
{
    int x;
    std::cin >> x;
    // передаем lambda в std::async
    auto f = std::async(std::launch::async, [](auto x) { return x * 2; }, x);
    auto val = f.get();
    std::cout << val << std::endl;
}
