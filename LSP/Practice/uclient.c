#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main(int argc, char *argv[]) {
    int sockfd, n, len;
    char recvline[1024];
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(atoi(argv[1]));
    len = sizeof(servaddr);
    printf("Give a number for server: ");
    scanf("%d", &n);
    sendto(sockfd, &n, 4, 0, (struct sockaddr *)&servaddr, len);
    recvfrom(sockfd, recvline, 50, 0, (struct sockaddr *)&servaddr, &len);
    recvline[n] = 0;
    printf("\nServer sent: %s\n", recvline);
    return 0;
}

