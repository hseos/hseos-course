#include <pthread.h>
#include <stdio.h>
#include <string.h>

void *func(void *ptr)
{
    printf("I'm thread\n");
    return NULL;
}

int main()
{
    pthread_t id = 0;

    int r = pthread_create(&id, NULL, func, NULL);
    if (r) {
        fprintf(stderr, "error: %s\n", strerror(r));
        return 1;
    }

    // ждем окончания нити
    //pthread_join(id, NULL);

    // завершаем "главную" нить без завершения процесса
    // процесс завершается когда завершаются все его нити
    pthread_exit(NULL);
}
