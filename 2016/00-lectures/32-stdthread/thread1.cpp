#include <thread>
#include <iostream>

void func()
{
    std::cout << "Thread" << std::endl;
}

int main()
{
    std::thread t(func);
    // перед вызовом деструктора должна быть выполнена либо операция join,
    // либо операция detach
    t.join();
    //t.detach();
}
