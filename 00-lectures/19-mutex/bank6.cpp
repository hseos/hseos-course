/*
Класс Account как монитор (синхронизированные методы).
 */

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <atomic>

using namespace std;

const int N1 = 100, N2 = 100;

class Account
{
    volatile double value;
    mutable pthread_mutex_t m;

public:
    Account(double initial) : value(initial)
    {
        pthread_mutexattr_t a;
        pthread_mutexattr_init(&a);
        pthread_mutexattr_settype(&a, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&m, &a);
        pthread_mutexattr_destroy(&a);
    }

    bool update(double val, double *p_newval)
    {
        bool result = false;
        pthread_mutex_lock(&m);
        if (value + val >= 0) {
            value += val;
            if (p_newval) *p_newval = value;
            result = true;
        }
        pthread_mutex_unlock(&m);
        return result;
    }
    double get() const
    {
        pthread_mutex_lock(&m);
        double val = value;
        pthread_mutex_unlock(&m);
        return val;
    }
};

Account deposit(100000), pocket(10000);

void *thread1_func(void *)
{
    while (1) {
        if (deposit.update(-1000, nullptr)) {
            pocket.update(1000, nullptr);
        }
        sched_yield();
    }
}

void *thread2_func(void *)
{
    while (1) {
        if (pocket.update(-1000, nullptr))
            deposit.update(1000, nullptr);
        sched_yield();
    }
}

int main()
{
    pthread_t *ids = new pthread_t[N1 + N2];
    for (int i = 0; i < N1; ++i) {
        pthread_create(&ids[i], NULL, thread1_func, NULL);
    }
    for (int i = 0; i < N2; ++i) {
        pthread_create(&ids[i + N1], NULL, thread2_func, NULL);
    }
    while (1) {
        double dep = deposit.get(), pock = pocket.get();
        printf("%g %g %g\n", dep, pock, dep + pock);
        usleep(100000);
    }
    for (int i = 0; i < N1 + N2; ++i) {
        pthread_join(ids[i], NULL);
    }
    return 0;
}
