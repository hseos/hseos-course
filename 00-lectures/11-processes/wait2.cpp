#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main()
{
	int p = fork();
	if (!p) {
		abort();
		return 1;
	} else {
		cout << "Pid: " << p << endl;
		sleep(120);
		int status = 0;
		int pid = wait(&status);
		cout << "Wait: " << pid << ", " << status << endl;
		cout << "exited? " << WIFEXITED(status) << " status: " << WEXITSTATUS(status) << endl;
		cout << "signaled? " << WIFSIGNALED(status) << " signo: " << WTERMSIG(status) << endl;
		cout << "core dumped? " << WCOREDUMP(status) << endl;
	}
}
