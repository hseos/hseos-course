/*
Использование pthread mutex для организации критических секций для доступа к переменным deposit и pocket.
 */

#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

const int N1 = 100, N2 = 100;

volatile double deposit = 100000, pocket = 10000;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *thread1_func(void *)
{
    while (1) {
        pthread_mutex_lock(&m);
        if (deposit >= 1000) {
            deposit -= 1000;
            pocket += 1000;
        }
        pthread_mutex_unlock(&m);
        sched_yield();
    }
}

void *thread2_func(void *)
{
    while (1) {
        pthread_mutex_lock(&m);
        if (pocket >= 1000) {
            deposit += 1000;
            pocket -= 1000;
        }
        pthread_mutex_unlock(&m);
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
        pthread_mutex_lock(&m);
        double dep = deposit, pock = pocket;
        pthread_mutex_unlock(&m);
        printf("%g %g %g\n", dep, pock, dep + pock);
        usleep(100000);
    }
    for (int i = 0; i < N1 + N2; ++i) {
        pthread_join(ids[i], NULL);
    }
    return 0;
}
