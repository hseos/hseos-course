#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

enum { COUNT = 100 };

// _unlocked-варианты стандартных функций нельзя использовать
// когда возможен одновременный их вызов из нескольких нитей!
// эта программа, скорее всего, завершится аварийно

void *func(void *ptr)
{
    int c;
    while ((c = getchar_unlocked()) != EOF) {
        putchar_unlocked(c);
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
