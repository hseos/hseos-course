#include <stdio.h>
#include <unistd.h>

int main()
{
	for (int i = 0; i < 4; ++i) {
		int p = fork();
		printf("%d\n", p);
	}
	sleep(100);
	return 0;
}
