/*
Организация критической секции с помощью атомарной операции обмена значений
на языки Си для компилятора GCC. В сгенерированном коде для x86 операции
__atomic_exchange_n соответствует одна инструкция xchgl.
 */

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

const int N1 = 100, N2 = 100;

volatile double deposit = 100000, pocket = 10000;

volatile int lock_var = 1;
void lock(volatile int *p)
{
    while (1) {
        int cur = __atomic_exchange_n(&lock_var, 0, __ATOMIC_ACQUIRE);
        if (cur) break;
        sched_yield();
    }
    *p = 0;
}
void unlock(volatile int *p)
{
    *p = 1;
}

void *thread1_func(void *)
{
    while (1) {
        lock(&lock_var);
        if (deposit >= 1000) {
            deposit -= 1000;
            pocket += 1000;
        }
        unlock(&lock_var);
        sched_yield();
    }
}

void *thread2_func(void *)
{
    while (1) {
        lock(&lock_var);
        if (pocket >= 1000) {
            deposit += 1000;
            pocket -= 1000;
        }
        unlock(&lock_var);
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
        lock(&lock_var);
        double dep = deposit, pock = pocket;
        unlock(&lock_var);
        printf("%g %g %g\n", dep, pock, dep + pock);
        usleep(100000);
    }
    for (int i = 0; i < N1 + N2; ++i) {
        pthread_join(ids[i], NULL);
    }
    return 0;
}
