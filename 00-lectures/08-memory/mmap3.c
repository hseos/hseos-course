#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    int pagesize = getpagesize();
    printf("page size: %d\n", pagesize);

    //int fd = open(argv[1], O_RDWR, 0);
    //printf("fd: %d\n", fd);
    void *mp = mmap(NULL, pagesize, PROT_READ | PROT_WRITE,
                    MAP_ANONYMOUS | MAP_SHARED, 0, 0);
    if (!~(intptr_t) mp) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }
    printf("ptr: %p\n", mp);
    fork();
    printf("pid: %d\n", getpid());
    int *data = mp;
    while (1) {
        printf("%d, %d, %d, %d\n", getpid(), data[0], data[1], data[2]);
        struct timeval tt;
        gettimeofday(&tt, NULL);
        data[0] = getpid();
        data[1] = tt.tv_sec;
        data[2] = tt.tv_usec;
        sleep(1);
    }
}
