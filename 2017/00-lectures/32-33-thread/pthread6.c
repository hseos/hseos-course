#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

enum { COUNT = 1000000 };

void *func(void *ptr)
{
    printf("%d\n", (int) (intptr_t) ptr);
    pause();
    return NULL;
}

pthread_t ids[COUNT];
int main()
{

    pthread_attr_t pa;
    pthread_attr_init(&pa);
    // минимальный размер стека на данной системе
    // на Linux - 16KiB
    pthread_attr_setstacksize(&pa, sysconf(_SC_THREAD_STACK_MIN));
    //pthread_attr_setstacksize(&pa, 16384);
    pthread_attr_setguardsize(&pa, 0);

    for (int i = 0; i < COUNT; ++i) {
        int r = pthread_create(&ids[i], &pa, func, (void*) (intptr_t) i);
        if (r) {
            fprintf(stderr, "%d: %s\n", i, strerror(r));
            pause();
        }
    }
    pthread_attr_destroy(&pa);

    for (int i = 0; i < COUNT; ++i) {
        pthread_join(ids[i], NULL);
    }
}
