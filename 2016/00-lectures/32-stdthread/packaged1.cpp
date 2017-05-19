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
    // создаем packaged_task для функции func
    // packaged_task пробрасывает возвращаемое значение и исключения
    std::packaged_task<int(int)> task(func);
    // получаем future для будущего использования
    auto f = task.get_future();
    // создаем нить и отдаем ей packaged_task
    std::thread thr(std::move(task), x);
    // ждем результата
    auto val = f.get();
    std::cout << val << std::endl;
    thr.join();
}
