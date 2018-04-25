#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

enum { COUNT = 100 };

// целое значение, помещающееся в указатель (например, int)
// можно передавать и так - преобразовывая его к указателю
// long long так передавать нельзя!
void *func(void *ptr)
{
    printf("%d\n", (int) (intptr_t) ptr);
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
