#include <sys/socket.h>
#include <stdio.h>
int main(){
	int sockfd;
	sockfd=socket(AF_INET, SOCK_STREAM,0);
	printf("%d",sockfd);
	return 0;
}


