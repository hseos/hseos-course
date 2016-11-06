/*
Организация барьеров.
 */

#include <pthread.h>
#include <iostream>
#include <unistd.h>

using namespace std;

const int N = 10;

pthread_mutex_t bm = PTHREAD_MUTEX_INITIALIZER ;
pthread_cond_t bc = PTHREAD_COND_INITIALIZER;
volatile int count;

pthread_mutex_t gm = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t gc = PTHREAD_COND_INITIALIZER;
volatile int flag;

void *thread_func(void *ptr)
{
    int self = (int)(size_t)(ptr);
    cout << -self << endl;
    pthread_mutex_lock(&bm);
    if (++count == N) {
        pthread_cond_signal(&bc);
    }
    pthread_mutex_unlock(&bm);

    pthread_mutex_lock(&gm);
    while (!flag)
        pthread_cond_wait(&gc, &gm);
    pthread_mutex_unlock(&gm);

    cout << self << endl;
    return NULL;
}

int main()
{
    pthread_t *ids = new pthread_t[N];
    for (int i = 0; i < N; ++i) {
        pthread_create(&ids[i], NULL, thread_func, (void*) (size_t) i);
    }
    pthread_mutex_lock(&bm);
    while (count != N)
        pthread_cond_wait(&bc, &bm);
    pthread_mutex_unlock(&bm);
    cout << "parent sleeps" << endl;
    sleep(5);

    pthread_mutex_lock(&gm);
    flag = 1;
    pthread_cond_broadcast(&gc);
    pthread_mutex_unlock(&gm);

    for (int i = 0; i < N; ++i)
        pthread_join(ids[i], NULL);
    return 0;
}
