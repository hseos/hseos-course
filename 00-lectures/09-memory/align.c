#include <stdio.h>

struct s1
{
    char c;
    long l;
};

struct s2
{
    char c;
    long long ll;
};

struct s3
{
    char c;
    double d;
};

struct s4
{
    char c;
    long double ld;
};

struct s5
{
    char c;
    void *vp;
};

#define OFFSET(t,f) ((size_t)(&((t*) 0)->f))

int main(int argc, char *argv[])
{
    printf("long: size: %zu, alignment: %zu\n", sizeof(long), OFFSET(struct s1, l));
    printf("long long: size: %zu, alignment: %zu\n", sizeof(long long), OFFSET(struct s2, ll));
    printf("double: size: %zu, alignment: %zu\n", sizeof(double), OFFSET(struct s3, d));
    printf("long double: size: %zu, alignment: %zu\n", sizeof(long double), OFFSET(struct s4, ld));
    printf("void *: size: %zu, alignment: %zu\n", sizeof(void *), OFFSET(struct s5, vp));
}

