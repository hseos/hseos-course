#include <signal.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void handle(int s)
{
    write(1, "TERM\n", 5);
}

int main()
{
    char buf[100];

    signal(SIGINT, handle);

    while (1) {
        int r = read(0, buf, sizeof(buf));
        if (r > 0) {
            write(1, buf, r);
        } else if (!r) {
            break;
        } else if (r < 0) {
            perror("");
        }
    }
}
