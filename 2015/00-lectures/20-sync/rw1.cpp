#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

using namespace std;

struct Message
{
    int producer = -1;
    int serial = 0;

    Message() = default;
    Message(int producer_, int serial_) : producer(producer_), serial(serial_) {}
};

const int BUF_SIZE = 32;
Message buffer[BUF_SIZE];
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int rcnt;
int wcnt;
pthread_cond_t rc = PTHREAD_COND_INITIALIZER;
pthread_cond_t wc = PTHREAD_COND_INITIALIZER;

void rlock()
{
    pthread_mutex_lock(&m);
    while (wcnt > 0) pthread_cond_wait(&rc, &m);
    ++rcnt;
    pthread_mutex_unlock(&m);
}

void runlock()
{
    pthread_mutex_lock(&m);
    if (!--rcnt) pthread_cond_broadcast(&wc);
    pthread_mutex_unlock(&m);
}

void wlock()
{
    pthread_mutex_lock(&m);
    while (rcnt > 0 || wcnt > 0) pthread_cond_wait(&wc, &m);
    ++wcnt;
    pthread_mutex_unlock(&m);
}

void wunlock()
{
    pthread_mutex_lock(&m);
    --wcnt;
    pthread_cond_broadcast(&wc);
    pthread_cond_broadcast(&rc);
    pthread_mutex_unlock(&m);
}

const int R_COUNT = 100;
const int W_COUNT = 100;

void *reader(void *ptr)
{
    int self = (int)(intptr_t)ptr;
    while (1) {
        int index = int(rand() / (RAND_MAX + 1.0) * BUF_SIZE);
        rlock();
        Message msg = buffer[index];
        usleep(10000);
        runlock();
        cout << self << " " << msg.producer << " " << msg.serial << endl;
        //sched_yield();
    }
    return 0;
}

void *writer(void *ptr)
{
    int self = (int)(intptr_t)ptr;
    int serial = 0;
    while (1) {
        int index = int(rand() / (RAND_MAX + 1.0) * BUF_SIZE);
        wlock();
        buffer[index] = Message{self, serial++};
        wunlock();
    }
    return 0;
}

int main()
{
    srand(time(0));
    pthread_t *ids = new pthread_t[R_COUNT + W_COUNT];
    int i = 0;
    for (; i < R_COUNT; ++i) {
        pthread_create(&ids[i], NULL, reader, (void*) (intptr_t) i);
    }
    for (; i < R_COUNT + W_COUNT; ++i) {
        pthread_create(&ids[i], NULL, writer, (void*) (intptr_t) i);
    }
    for (i = 0; i < R_COUNT + W_COUNT; ++i) {
        pthread_join(ids[i], NULL);
    }
}
