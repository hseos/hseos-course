#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
Преобразование имени хоста и имени сервиса,
заданных в аргументах командной строки,
во внутреннее представление для IPv6.
В качестве имени хоста поддерживается и DNS-имя, и IP-адрес.
В качестве имени сервиса поддерживается и имя (https), и номер порта (443).
*/

int main(int argc, char *argv[])
{
    struct addrinfo hints = { .ai_family = AF_INET6, .ai_socktype = SOCK_STREAM };
    struct addrinfo *addrs = NULL;

    int res = getaddrinfo(argv[1], argv[2], &hints, &addrs);
    printf("%d\n", res);
    if (!res) {
        // просматриваем все найденные адреса
        for (struct addrinfo *pa = addrs; pa; pa = pa->ai_next) {
            // адрес является адресом формата AF_INET6
            struct sockaddr_in6 *psin = (struct sockaddr_in6 *) pa->ai_addr;
            // выводим IP-адрес как строку
            char buf[256];
            printf("%s\n", inet_ntop(AF_INET6, &psin->sin6_addr, buf, sizeof(buf)));
        }
        freeaddrinfo(addrs);
    } else {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
    }
}
