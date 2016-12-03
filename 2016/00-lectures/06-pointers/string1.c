#include <stdio.h>

/*
строковые литералы "..." размещаются в области
программы, недоступной на запись
*/
int main(void)
{
    char *s = "abcd"; // s - указатель в read-only memory
    s[2] = 'e'; // undefined behavior - на практике segmentation fault
    printf("%s\n", s);
}
