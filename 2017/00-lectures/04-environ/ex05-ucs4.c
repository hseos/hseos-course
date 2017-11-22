#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main()
{
    // для работы с wide chars вызов setlocale обязателен
    setlocale(LC_ALL, "");

    // не забываем везде добавлять L :)
    wchar_t c;
    wchar_t *lstr = L"оавлфваsdfsdfsdf";
    wprintf(L"%Ls\n", lstr);
}
