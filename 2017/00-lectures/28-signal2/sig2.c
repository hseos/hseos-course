#include <signal.h>
#include <stdio.h>

int main()
{
    // игнорирование сигнала Floating Point Exception
    // не приведет ни к чему хорошему
    // процесс все равно завершится при ошибке деления на 0
    signal(SIGFPE, SIG_IGN);
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", a / b);
}
