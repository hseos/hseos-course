#include <stdio.h>
#include <wchar.h>
#include <locale.h>

/*
используем Wide Char API для обработки текста
*/
int main(void)
{
    wchar_t c;
    setlocale(LC_ALL, "");
    while ((c = getwc(stdin)) != EOF) {
        wprintf(L"%Lc\n", (int) c);
    }
}
