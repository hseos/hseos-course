#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

const int THR_COUNT = 3;

struct PhilInfo
{
    pthread_t id;
    char state = '?';
    bool termflag = false;

    long long wt = 0;
    long long et = 0;
    long long tt = 0;
};

pthread_mutex_t *forks;
PhilInfo *phils;

void get_fork(int n)
{
    pthread_mutex_lock(&forks[n]);
}

void put_fork(int n)
{
    pthread_mutex_unlock(&forks[n]);
}

void *philosopher(void *ptr)
{
    int self = (int)(intptr_t) ptr;
    int next = (self + 1) % THR_COUNT;
    PhilInfo *info = &phils[self];
    while (!info->termflag) {
        info->state = 'W';
        get_fork(self);
        usleep(1000);
        //sched_yield();
        get_fork(next);
        info->state = 'E';
        usleep(10000);
        put_fork(next);
        put_fork(self);
        info->state = 'T';
        usleep(10000);
    }
    return NULL;
}

void *watcher(void *ptr)
{
    while (1) {
        for (int i = 0; i < THR_COUNT; ++i)
            putchar(phils[i].state);
        putchar('\r');
        fflush(stdout);
        usleep(100000);
    }
}

void *timerthread(void *ptr)
{
    sleep(60);
    for (int i = 0; i < THR_COUNT; ++i)
        phils[i].termflag = true;
    return NULL;
}

int main()
{
    forks = new pthread_mutex_t[THR_COUNT];
    phils = new PhilInfo[THR_COUNT];

    for (int i = 0; i < THR_COUNT; ++i)
        pthread_mutex_init(&forks[i], NULL);
    for (int i = 0; i < THR_COUNT; ++i)
        pthread_create(&phils[i].id, NULL, philosopher, (void*)(intptr_t) i);

    pthread_t wid;
    pthread_create(&wid, NULL, watcher, NULL);
    pthread_t tid;
    pthread_create(&tid, NULL, timerthread, NULL);

    for (int i = 0; i < THR_COUNT; ++i)
        pthread_join(phils[i].id, NULL);
}
