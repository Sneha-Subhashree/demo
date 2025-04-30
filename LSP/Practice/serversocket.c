/*Socket - Day Time Server*/
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

int main(int argc, char **argv) {
    int listenfd, connfd, len, n;
    //char recvline[1024];
    char buff[1024];
    struct sockaddr_in servaddr, clientaddr;
    len = sizeof(struct sockaddr_in);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(0);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    getsockname(listenfd, (struct sockaddr *)&servaddr, &len);

    printf("After bind ephemeral port = %d\n", (int)ntohs(servaddr.sin_port));

    listen(listenfd, 5);

    connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &len);

    for (;;) {
        bzero(buff, sizeof(buff));
        read(connfd, buff, sizeof(buff));
        printf("From client: %s", buff);

        n = 0;

        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;

        // and send that buffer to client
        write(connfd, buff, sizeof(buff));
    }

    // Optional commented lines:
    // n = read(connfd, recvline, 1024);
    // printf("%d\n", n);
    // recvline[n] = 0;
    // printf("assign recvline\n");
    // write(connfd, "hello", 6);

    close(connfd);
}

