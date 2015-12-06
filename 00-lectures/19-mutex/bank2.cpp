/*
Наивная организация критической секции. Из-за отсутствия атомарности при работе с памятью
целостность данных со временем разрушается.
 */

#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

const int N1 = 100, N2 = 100;

volatile double deposit = 100000, pocket = 10000;

volatile int lock_var = 1;
void lock(volatile int *p)
{
    while (!*p) { sched_yield(); }
    sched_yield();
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
