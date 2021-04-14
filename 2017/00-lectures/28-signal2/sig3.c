#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int flag = 0;

void handler(int s)
{
    flag = 1;
}

int main()
{
    // для установки обработчика сигнала лучше всего sigaction
    // не используйте signal!
    sigaction(SIGINT, 
                &(struct sigaction){ .sa_handler = handler, 
                                    .sa_flags = SA_RESTART }, NULL);

    // перехватываем сигнал SIGINT
    long long z = 0;
    while (1) {
        if (flag) {
            printf("signal %d\n", getpid());
            flag = 0;
        }
        printf("%lld\n", z++);
    }
}
