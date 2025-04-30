/* Socket : UDP Server */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main(int argc, char **argv) {
    int sockfd, p, len;
    struct sockaddr_in servaddr, clientaddr;
    char buff[1024];
    len = sizeof(struct sockaddr_in);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(0);
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    getsockname(sockfd, (struct sockaddr *)&servaddr, &len);
    printf("After bind ephemeral port = %d\n", ntohs(servaddr.sin_port));
    recvfrom(sockfd, &p, 4, 0, (struct sockaddr *)&clientaddr, &len);
    printf("\nClient send: %d\n", p);
    printf("\nGive a string to send for client: ");
    scanf("%s", buff);
    sendto(sockfd, buff, 50, 0, (struct sockaddr *)&clientaddr, len);
    close(sockfd);
    return 0;
}

