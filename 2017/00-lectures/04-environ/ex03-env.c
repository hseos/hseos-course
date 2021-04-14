#include <stdio.h>
#include <stdlib.h>

// можем использовать глобальную переменную environ
// но для этого должны ее объявить явно
//extern char **environ;

// можем использовать параметр 'envp' функции main
int main(int argc, char *argv[], char *envp[])
{
    // берем переменную окружения по имени
    char *s = getenv("PATH");
    printf("%s\n", s);

    // все переменные окружения со значениями
    for (int i = 0; envp[i]; ++i) {
        printf("%s\n", envp[i]);
    }
}
