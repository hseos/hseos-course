#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

enum { COUNT = 1000000 };

// стресс-тест на число нитей, которое можно создать
void *func(void *ptr)
{
    printf("%d\n", (int) (intptr_t) ptr);
    pause();
    return NULL;
}

pthread_t ids[COUNT];
int main()
{

    for (int i = 0; i < COUNT; ++i) {
        int r = pthread_create(&ids[i], NULL, func, (void*) (intptr_t) i);
        if (r) {
            fprintf(stderr, "%d: %s\n", i, strerror(r));
            pause();
        }
    }

    for (int i = 0; i < COUNT; ++i) {
        pthread_join(ids[i], NULL);
    }
}
