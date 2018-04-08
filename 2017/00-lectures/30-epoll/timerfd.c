#include <sys/timerfd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd = timerfd_create(CLOCK_REALTIME, 0);
    if (fd < 0) {
        perror("");
        exit(1);
    }
    struct itimerspec its =
    {
        .it_interval = { .tv_sec = 0, .tv_nsec = 10000 },
        .it_value = { .tv_sec = 2 }
    };
    timerfd_settime(fd, 0, &its, NULL);
    unsigned long long value;
    while (read(fd, &value, sizeof(value)) == sizeof(value)) {
        printf("%llu\n", value);
    }
}
