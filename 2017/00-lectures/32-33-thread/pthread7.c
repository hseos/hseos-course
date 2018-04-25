#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// принудительное завершение нити
volatile int val;
void *func(void *ptr)
{
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    printf("before pause()\n");
    for (int i = 1; i < 2000000000; ++i) {
        int j;
        for (j = 2; j < i; ++j) {
            if (!(i % j)) break;
        } 
        if (j < i) {
            printf("%d\n", i);
            val = i;
        }
    }
    printf("after pause()\n");
    return NULL;
}

int main()
{
    pthread_t tid = 0;

    pthread_create(&tid, NULL, func, NULL);

    usleep(1000000);

    //////
    pthread_cancel(tid);

    pthread_join(tid, NULL);
}
