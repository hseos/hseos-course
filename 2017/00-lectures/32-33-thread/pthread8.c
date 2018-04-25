#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

enum { COUNT = 100 };

// Thread-local storage (TLS)
_Thread_local int cnt = 100;

void *func(void *ptr)
{
    printf("%d %d\n", (int) (intptr_t) ptr, cnt++);
    return NULL;
}

int main()
{
    pthread_t ids[COUNT];

    for (int i = 0; i < COUNT; ++i) {
        pthread_create(&ids[i], NULL, func, (void*) (intptr_t) i);
    }

    for (int i = 0; i < COUNT; ++i) {
        pthread_join(ids[i], NULL);
    }
}
