/* Socket - Day Time Client */
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int sockfd, n, connlen;
    // char recvline[1024];
    char buff[1024];
    struct sockaddr_in servaddr;

    connlen = sizeof(struct sockaddr_in);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); // Get IP from argument
    servaddr.sin_port = htons(atoi(argv[2]));      // Get port from argument

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    for (;;) {
        // bzero(buff, sizeof(buff));
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;

        write(sockfd, buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server: %s", buff);
    }

    // Optional commented code:
    // write(sockfd, "Hi", 3);
    // n = read(sockfd, recvline, 1024);
    // printf("%d\n", n);
    // recvline[n] = 0;
    // printf("%s\n", recvline);

    close(sockfd);
}

