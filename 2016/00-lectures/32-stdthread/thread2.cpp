#include <thread>
#include <iostream>

void func(int x, int y)
{
    std::cout << "Thread: " << x << " " << y << std::endl;
}

int main()
{
    // передача в нить произвольного числа аргументов произвольного типа
    std::thread t(func, 1, 2);
    t.join();
}
