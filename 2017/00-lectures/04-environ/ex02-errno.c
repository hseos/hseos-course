#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// использование переменной errno и функции strerror
// для вывода сообщения об ошибки в текущей локали пользователя
int main()
{
    // берем настройки локали из переменных окружения
    setlocale(LC_ALL, "");
    FILE *f = fopen("abc.txt", "r");
    if (!f) {
        fprintf(stderr, "error: %s\n", strerror(errno));
        exit(1);
    }
}
