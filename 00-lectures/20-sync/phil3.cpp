#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

const int THR_COUNT = 72;

struct PhilInfo
{
    pthread_t id;
    char state = '?';
    bool termflag = false;

    long long wt = 0;
    long long et = 0;
    long long tt = 0;
};

pthread_mutex_t biglock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitlist = PTHREAD_COND_INITIALIZER;
PhilInfo *phils;

 void *philosopher(void *ptr)
 {
     int self = (int)(intptr_t) ptr;
     int next = (self + 1) % THR_COUNT;
     int prev = (self + THR_COUNT - 1) % THR_COUNT;
     PhilInfo *info = &phils[self];
     while (!info->termflag) {
         pthread_mutex_lock(&biglock);
         info->state = 'W';
         while (phils[prev].state == 'E' || phils[next].state == 'E') {
             pthread_cond_wait(&waitlist, &biglock);
         }
         info->state = 'E';
         pthread_mutex_unlock(&biglock);
         usleep(10000);
         pthread_mutex_lock(&biglock);
         info->state = 'T';
         pthread_cond_broadcast(&waitlist);
         pthread_mutex_unlock(&biglock);
         usleep(50000);
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
    phils = new PhilInfo[THR_COUNT];

    for (int i = 0; i < THR_COUNT; ++i)
        pthread_create(&phils[i].id, NULL, philosopher, (void*)(intptr_t) i);

    pthread_t wid;
    pthread_create(&wid, NULL, watcher, NULL);
    pthread_t tid;
    pthread_create(&tid, NULL, timerthread, NULL);

    for (int i = 0; i < THR_COUNT; ++i)
        pthread_join(phils[i].id, NULL);
}
