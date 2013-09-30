#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define MAXLINE 1024
int main() {
	int n,sockfd,connfd;
	char buf[1024];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port=htons(6666);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	//	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	//	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	listen(sockfd, 1);
	while (1) {
		// connfd = accept(sockfd, (struct sockaddr *) NULL, NULL);
		// n = recv(connfd, buf, MAXLINE, 0);
		// buf[n] = '\0';
		// printf("the msg recved is %s\n", buf);
	}
}