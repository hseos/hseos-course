#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int count;
char *states;
pthread_mutex_t *forks;
pthread_t *ids;

void *phil(void *ptr)
{
    int self = (int)(intptr_t)ptr;
    while (1) {
        states[self] = 'T';
        usleep(200000);
        states[self] = 'W';
        int f1 = self;
        int f2 = self + 1;
        if (f2 == count) {
            f1 = 0;
            f2 = self;
        }
        // захватываем вилки: сначала с меньшим номером, затем с большим
        pthread_mutex_lock(&forks[f1]);
        pthread_mutex_lock(&forks[f2]);
        states[self] = 'E';
        usleep(200000);
        // освобождаем вилки в порядке, обратном к захвату
        pthread_mutex_unlock(&forks[f2]);
        pthread_mutex_unlock(&forks[f1]);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    count = strtol(argv[1], NULL, 10);
    states = malloc(count + 1);
    memset(states, '?', count);
    states[count] = 0;
    forks = malloc(count * sizeof(forks[0]));
    for (int i = 0; i < count; ++i) {
        pthread_mutex_init(&forks[i], NULL);
    }
    ids = malloc(count * sizeof(ids[0]));

    for (int i = 0; i < count; ++i) {
        pthread_create(&ids[i], NULL, phil, (void*) (intptr_t) i);
    }

    while (1) {
        printf("%s\r", states); fflush(stdout);
        usleep(100000);
    }
}
