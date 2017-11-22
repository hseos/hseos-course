#include <stdio.h>

// null-terminated strings
int main()
{
    char s[] = "abcdef"; // sizeof(s) == 7
    char s2[] = { 'a', 'b', 'c', 0 }; // sizeof(s2) == 4
    const char s3[] = "abcdefg";

    char *s4 = "aaabusdf";
    const char *s5 = "hdsfasdfdsaF";

    //s5[3] = 'a'; // ошибка компиляции
    //s4[5] = 'z'; // скомпилируется, но при запуске Segmentation Fault 
    s[3] = 'G';
    printf("%s\n", s);
}
