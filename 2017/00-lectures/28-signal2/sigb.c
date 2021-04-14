#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

// нелокальные переходы для выхода из обработчика сигнала

jmp_buf jb;

void handler(int s)
{
    printf("division by zero\n");
    siglongjmp(jb, 1);
}

int main()
{
    signal(SIGFPE, handler);
    int a, b;
    while (scanf("%d%d", &a, &b) == 2) {
        if (!sigsetjmp(jb, 1)) {
            int c = a / b;
            printf("%d\n", c);
        } else {
            printf("resuming\n");
        }
    }
}
