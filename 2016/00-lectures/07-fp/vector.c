#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t reserved = 16;
    size_t used = 0;
    int *data = malloc(reserved * sizeof(*data));
    // int *data = (int*) malloc(reserved * sizeof(int)); -- плохо
    int x;

    while (scanf("%d", &x) == 1) {
        if (used == reserved) {
            data = realloc(data, (reserved *= 2) * sizeof(*data));
        }
        data[used++] = x;
    }

    for (ssize_t i = (ssize_t) used - 1; i >= 0; --i) {
        printf("%d\n", data[i]);
    }
}
