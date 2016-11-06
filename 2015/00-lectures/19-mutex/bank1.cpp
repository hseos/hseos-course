/*
Работа с общими для нитей переменными (deposit, pocket) без взаимной блокировки.
Со временем целостность данных будет нарушена из-за гонок между нитями.
 */

#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

const int N1 = 100, N2 = 100;

double deposit = 100000, pocket = 10000;

void *thread1_func(void *)
{
    while (1) {
        if (deposit >= 1000) {
            deposit -= 1000;
            pocket += 1000;
        }
        sched_yield();
    }
}

void *thread2_func(void *)
{
    while (1) {
        if (pocket >= 1000) {
            deposit += 1000;
            pocket -= 1000;
        }
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
        double dep = deposit, pock = pocket;
        printf("%g %g %g\n", dep, pock, dep + pock);
        usleep(100000);
    }
    for (int i = 0; i < N1 + N2; ++i) {
        pthread_join(ids[i], NULL);
    }
    return 0;
}
