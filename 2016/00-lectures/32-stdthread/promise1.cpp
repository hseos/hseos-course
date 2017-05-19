#include <thread>
#include <iostream>
#include <future>
#include <chrono>

void func(int n, std::promise<int> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // сохраняем результат и активируем ждущую нить
    p.set_value(n + 100);
}

int main()
{
    // создается promise для возврата значения int
    std::promise<int> promise;
    // получаем future для будущего использования
    // в C++11 - c++14 надо писать future<int>
    std::future future = promise.get_future();
    // создаем нить и отдаем ей promise
    std::thread thr(func, 100, std::move(promise));
    // ждем результата от нити и печатаем его
    std::cout << future.get() << std::endl;
    thr.join();
}
