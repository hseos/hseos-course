#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define N 1000000
int count = 10;

void *thread_func(void *arg)
{
    int serial = (int) arg;
    //printf("me: %d\n", serial);
    for (int i = 0; i < 2; ++i) {
        ++count;
        printf("%d %d\n", serial, count);
    }
    sleep(1200);
    return NULL;
}

int main()
{
    pthread_t ids[N];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 16384);
    pthread_attr_setguardsize(&attr, 0);
    for (int i = 0; i < N; ++i) {
        int r = pthread_create(&ids[i], &attr, thread_func, (void*) i);
        if (r > 0) {
            fprintf(stderr, "error: %d, %s\n", i, strerror(r));
            exit(1);
        }
    }
    pthread_attr_destroy(&attr);
    for (int i = 0; i < N; ++i) {
        pthread_join(ids[i], NULL);
    }
}
