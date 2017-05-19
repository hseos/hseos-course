#include <thread>
#include <iostream>
#include <future>
#include <chrono>

void func(int n, std::promise<int> p)
{
    try {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        throw 50;
        p.set_value(n + 100);
    } catch (...) {
        // пробрасываем исключение в ожидающую нить
        p.set_exception(std::current_exception());
    }
}

int main()
{
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    std::thread thr(func, 100, std::move(promise));
    try {
        std::cout << future.get() << std::endl;
    } catch (int value) {
        // ловим проброшенное из нити исключение
        std::cout << "exception " << value << std::endl;
    }
    thr.join();
}
