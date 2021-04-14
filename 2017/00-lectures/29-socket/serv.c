#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
простой сервер, принимает от клиента поток байт,
возвращает клиенту строку Hello
 */

int main(int argc, char *argv[])
{
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    // следующие два системных вызова предписывают освободить серверный порт
    // немедленно по окончании работы процесса
    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));

    // привязываем сокет к порту
    // входящий адрес - любой
    // номер порта - argv[1]
    struct sockaddr_in s1;
    s1.sin_family = AF_INET;
    s1.sin_port = htons(strtol(argv[1], NULL, 10));
    s1.sin_addr.s_addr = INADDR_ANY;
    int r = bind(fd, (struct sockaddr*) &s1, sizeof(struct sockaddr_in));
    if (r < 0) {
        perror("bind");
        return 1;
    }

    // переключаем сокет в режим прослушивания
    listen(fd, 5);

    while (1) {
        // получаем новое подключение
        struct sockaddr_in s2;
        socklen_t slen = sizeof(s2); // обратие внимание, что именно socklen_t, не size_t!
        int fd2 = accept(fd, (struct sockaddr*) &s2, &slen);

        // для каждого клиента создаем отдельный процесс
        if (!fork()) {
            close(fd);
            char c;
            while (read(fd2, &c, 1) == 1) {
                write(1, &c, 1);
            }

            write(fd2, "Hello\n", 6);
            _exit(0);
        }
        close(fd2);

        // FIXME: будут накапливаться zombi-процессы
        // отец должен получать статус завершившихся сыновей!
    }
}
