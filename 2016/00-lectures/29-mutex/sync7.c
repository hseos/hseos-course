#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdatomic.h>

volatile long long var1 = 0;
volatile long long var2 = 0;

long long m  = 1;

void *thread_func(void *ptr)
{
    int id = *(int*) ptr;
    for (int i = 0; i < 10000000; ++i) {
        // критическая секция на spinlock
        asm("movq $0, %%rax\n"
            "0: xchgq m, %%rax\n"
            "testq %%rax, %%rax\n"
            "jz 0b\n" : : : "rax");
	    var1 += id;
    	var2 -= id;
        asm("movq $1, %%rax\n"
            "1: xchgq m, %%rax\n"
            : : : "rax");
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
