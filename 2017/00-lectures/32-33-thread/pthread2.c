#include <stdio.h>
#include <pthread.h>

enum { COUNT = 100 };

// DATA RACE при обращении к переменной i
// никогда так не делайте!
// для диагностики data race используйте опцию -fsanitize=thread
void *func(void *ptr)
{
    printf("%d\n", *(int*) ptr);
    return NULL;
}

int main()
{
    pthread_t ids[COUNT];

    for (int i = 0; i < COUNT; ++i) {
        pthread_create(&ids[i], NULL, func, &i);
    }

    for (int i = 0; i < COUNT; ++i) {
        pthread_join(ids[i], NULL);
    }
}
