#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

// Undefined behavior (UB) при обращении по нулевому указателю,
// даже если обращение по нулевому адресу допустимо аппаратурой
// запускать из-под пользователя root
// сравните запуск неоптимизированной и оптимизированной программы
int main(int argc, char *argv[])
{
    // отображаем виртуальную память по нулевому адресу
    unsigned char *ptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_FIXED, -1, 0);
    if (ptr == MAP_FAILED) {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return 1;
    }
    // печатаем значение указателя, должно быть 0 или nil
    printf("%p\n", ptr);
    *ptr = 'A'; // физически это допустимое обращение по нулевому указателю
    if (ptr == NULL) {
        // эта ветвь может быть удалена при оптимизации
        printf("%c\n", 'B');
    } else {
        printf("%c\n", 'C');
    }
}
