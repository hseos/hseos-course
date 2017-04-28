#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdatomic.h>

volatile long long var1 = 0;
volatile long long var2 = 0;

void *thread_func(void *ptr)
{
    int id = *(int*) ptr;
    for (int i = 0; i < 10000000; ++i) {
        // data race при обращении к var1 и var2
        // получим случайные неправильные результаты
	    var1 += id;
	    var2 -= id;
    }
    return (void*) (intptr_t) id;
}

int main(int argc, char *argv[])
{
    int count = strtol(argv[1], NULL, 10);
    pthread_t *ids = calloc(count, sizeof (*ids));
    int *nums = calloc(count, sizeof (*nums));
    for (int i = 0; i < count; ++i) {
        nums[i] = i;
        int err = pthread_create(&ids[i], NULL, thread_func, &nums[i]);
        if (err) {
            printf("total: %d, %s\n", i, strerror(err));
            break;
        }
    }
    for (int i = 0; i < count; ++i) {
        void *res;
        pthread_join(ids[i], &res);
    }
    printf("%lld %lld\n", var1, var2);
}
