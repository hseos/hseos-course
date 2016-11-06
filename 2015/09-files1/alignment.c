#include <stdio.h>

#define OFFSETOF(t, f) ((size_t)&(((t*) NULL)->f))

struct s
{
	char f1;
	long long f2;
	char f3;
};

int main(void)
{
	struct s ss;

	printf("%zu\n", sizeof(ss));
	printf("%zu\n", OFFSETOF(struct s, f1));
	printf("%zu\n", OFFSETOF(struct s, f2));
	printf("%zu\n", OFFSETOF(struct s, f3));
	return 0;
}
