#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

enum { COUNT = 100 };

void *func(void *ptr)
{
    int c;
    // обычно стандартные функции (например, getchar)
    // потокобезопасны (thread-safe)
    // но в данном примере операция getchar() - putchar() не атомарна!
    // что приводит к порче данных
    while ((c = getchar()) != EOF) {
        putchar(c);
    }
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
