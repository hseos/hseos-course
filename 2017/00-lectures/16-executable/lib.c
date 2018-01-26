#include <stdio.h>

extern int mainVar;
int libVar = 20;

void mainFunc(void);

void libFunc(void)
{
    mainFunc();
    ++libVar;
    printf("%d %d\n", mainVar, libVar);
}
