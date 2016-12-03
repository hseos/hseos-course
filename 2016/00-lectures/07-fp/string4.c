#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { STRING_OPT_SIZE = 8 };

struct String
{
    size_t size;
    char *str;
};

struct String *string_alloc(const char *str)
{
    size_t len = strlen(str);
    struct String *s = calloc(1, sizeof(*s));
    s->size = len;
    s->str = strdup(str);
    return s;
}

int main(void)
{
    char buf[64];
    for (int i = 0; i < 4 * 1024 * 1024; ++i) {
        sprintf(buf, "%d", i);
        string_alloc(buf);
    }
    //getchar();
}
