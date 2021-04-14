#include <stdio.h>

// эта программа выводит на стандартный поток вывода
// свое имя, затем аргументы командной строки, затем NULL
int main(int argc, char *argv[])
{
    for (int i = 0; i <= argc; ++i) {
        printf("[%d]: %s\n", i, argv[i]);
    }
}
