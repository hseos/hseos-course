#include <thread>
#include <iostream>
#include <vector>

void func(int x, int y)
{
    std::cout << "Thread: " << x << " " << y << std::endl;
}

int main()
{
    std::thread t1(func, 1, 2);
    // вызовется terminate, так как нить,
    // созданная в предыдущей строке,
    // находится в активном состоянии
    t1 = std::thread(func, 2, 3);
    t1.join();
}
