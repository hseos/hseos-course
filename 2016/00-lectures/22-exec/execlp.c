#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    execlp(argv[1], "cat", "1", "2", "3", NULL);
    perror("execlp");
}
