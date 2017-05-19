#include <future>
#include <thread>
#include <iostream>

int func(int x)
{
    throw x * 1.5;
    return x * 2;
}

int main()
{
    int x;
    std::cin >> x;
    // std::async автоматически пробрасывает исключения в ждущую нить
    auto f = std::async(std::launch::async, func, x);
    try {
        auto val = f.get();
        std::cout << val << std::endl;
    } catch (double value) {
        std::cout << "double " << value << std::endl;
    }
}
