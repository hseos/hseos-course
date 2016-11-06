#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ext/stdio_filebuf.h>

int main()
{
    int p[2];

    pipe(p);
    if (!fork()) {
        dup2(p[0], 0); close(p[0]); close(p[1]);
        execlp("cat", "cat", NULL);
    }

    close(p[0]);

    {
        __gnu_cxx::stdio_filebuf<char> filebuf(p[1], std::ios::out);
        std::ostream os(&filebuf);

        std::cout << filebuf.fd() << std::endl;

        os << 1 << " "; os.flush();
        sleep(1);
        os << 2 << " "; os.flush();
        sleep(1);
        os << 3 << std::endl;
    }

    wait(NULL);
    return 0;
}
