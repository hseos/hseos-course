#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    int pid, status;
    // запускаем 10 процессов
    for (int i = 0; i < 10; ++i) {
        pid = fork();
        if (!pid) {
            // в сыне выполняем действия
            srand(time(0) + getpid());
            usleep(10000*(rand() %20 + 1));
            _exit(i);
        }
    }
    // здесь код отца
    for (int i = 0; i < 10; ++i) {
        // while ((pid = wait(&status)) > 0) {
        pid = wait(&status);
        printf("pid: %d, завершился с кодом: %d\n",
            pid, WEXITSTATUS(status));
    }
}
