#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// использование volatile sig_atomic_t для переменных-флагов сигнала
volatile sig_atomic_t flag = 0;

void handler(int s)
{
    flag = 1;
}

int main()
{
    //signal(SIGINT, handler);
    sigaction(SIGINT, 
                &(struct sigaction){ .sa_handler = handler, 
                                    .sa_flags = SA_RESTART }, NULL);

    while (1) {
        // BUSY WAIT - это очень плохо!
        while (!flag) {} // BUSY WAIT
        printf("signal %d\n", getpid());
        flag = 0;
    }
}
