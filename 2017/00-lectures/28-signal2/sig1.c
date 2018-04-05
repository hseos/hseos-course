#include <signal.h>
#include <stdio.h>

int main()
{
    // отправка сигнала самому себе
    // процесс гарантированно получит SIGBUS
    // еще до того, как завершится вызов raise()
    raise(SIGBUS);
    printf("yes\n");
}
