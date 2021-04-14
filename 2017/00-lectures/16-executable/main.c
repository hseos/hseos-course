#include <stdio.h>

int mainVar = 10;
extern int libVar;

void libFunc(void);
void asmFunc(void);

void mainFunc(void)
{
    printf("%d %d\n", mainVar, libVar);
}

int main(void)
{
    asmFunc();
    mainFunc();
    libFunc();
    getchar();
}
