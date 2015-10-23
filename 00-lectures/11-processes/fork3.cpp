#include <stdio.h>
#include <unistd.h>
#include <sched.h>

int main()
{
	int p = fork();
	if (p > 0) sched_yield();
	printf("%d\n", p);
	return 0;
}
