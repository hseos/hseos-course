#include <stdio.h>
#include <pthread.h>

enum { COUNT = 100 };

void *func(void *ptr)
{
    printf("%d\n", *(int*) ptr);
    return NULL;
}

int main()
{
    pthread_t ids[COUNT];
    int ids2[COUNT];

    for (int i = 0; i < COUNT; ++i) {
        // передаем id нити таким образом, чтобы не возникал data race
        ids2[i] = i;
        pthread_create(&ids[i], NULL, func, &ids2[i]);
    }

    for (int i = 0; i < COUNT; ++i) {
        pthread_join(ids[i], NULL);
    }
}
