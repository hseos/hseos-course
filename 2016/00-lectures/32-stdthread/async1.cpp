#include <future>
#include <thread>
#include <iostream>

int func(int x)
{
    return x * 2;
}

int main()
{
    int x;
    std::cin >> x;
    // создаем асинхронную задачу
    // в качестве возвращаемого значения получаем future
    auto f = std::async(std::launch::async, func, x);
    auto val = f.get();
    std::cout << val << std::endl;
}
