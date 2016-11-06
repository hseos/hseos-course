#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include <iostream>

using namespace std;

struct Message
{
    int producer;
    int serial;
};

const int Q_SIZE = 16;

Message buffer[Q_SIZE];
int head, size;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ec = PTHREAD_COND_INITIALIZER;
pthread_cond_t fc = PTHREAD_COND_INITIALIZER;

void get(Message &msg)
{
    pthread_mutex_lock(&m);
    while (size == 0) {
        pthread_cond_wait(&ec, &m);
    }
    msg = buffer[head];
    head = (head + 1) % Q_SIZE;
    if (size-- == Q_SIZE) {
        pthread_cond_broadcast(&fc);
    }
    pthread_mutex_unlock(&m);
}

void put(const Message &msg)
{
    pthread_mutex_lock(&m);
    while (size == Q_SIZE) {
        pthread_cond_wait(&fc, &m);
    }
    buffer[(head + size) % Q_SIZE] = msg;
    if (size++ == 0) {
        pthread_cond_broadcast(&ec);
    }
    pthread_mutex_unlock(&m);
}

const int PROD_COUNT = 100;
const int CONS_COUNT = 100;

void *producer(void *ptr)
{
    int self = (int)(intptr_t) ptr;
    int serial = 0;

    while (1) {
        put(Message{self, serial++});
        usleep(100000);
    }
}

void *consumer(void *ptr)
{
    int self = (int)(intptr_t) ptr;
    while (1) {
        Message msg;
        get(msg);
        cout << self << " " << msg.producer << " " << msg.serial << endl;
        sched_yield();
    }
}

int main()
{
    pthread_t *ids = new pthread_t[PROD_COUNT + CONS_COUNT];
    int i = 0;
    for (; i < PROD_COUNT; ++i) {
        pthread_create(&ids[i], NULL, producer, (void*) (intptr_t) i);
    }
    for (; i < PROD_COUNT + CONS_COUNT; ++i) {
        pthread_create(&ids[i], NULL, consumer, (void *) (intptr_t) i);
    }

    for (i = 0; i < PROD_COUNT + CONS_COUNT; ++i) {
        pthread_join(ids[i], NULL);
    }
}
