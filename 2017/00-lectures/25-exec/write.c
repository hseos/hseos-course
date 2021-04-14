#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sched.h>

int main()
{
    char buf[10];
    for (int i = 0; i < 10; ++i) {
        if (!fork()) {
            for (int j = 0; j < 9; ++j) {
                buf[j] = '0' + i;
            }
            buf[9] = '\n';
            /*
            for (int j = 0; j < 10; ++j) {
                write(1, &buf[j], 1);
                sched_yield();
            }
*/
            write(1, &buf[0], sizeof(buf));
            _exit(0);
        }
    }

    while (wait(NULL) > 0) {}
}
