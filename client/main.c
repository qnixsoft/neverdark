#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include "tty.h"

#define FIXEDSTR(a) a, (sizeof(a) + 1)

int
main(int argc, char *argv[], char *envp[])
{
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 
	char inbuf[2 * BUFSIZ];
	char outbuf[4 * BUFSIZ];

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd < 0) {
		perror("socket");
		return -1;
	}

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(4201); 

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) != 0) { 
		perror("connect");
		return -1;
	} 

	write(sockfd, FIXEDSTR("auth One qovmjbl")); 

	for (;;) {
		ssize_t ret = read(sockfd, inbuf, sizeof(inbuf));
		if (ret <= 0)
			break;
		inbuf[ret] = '\0';
		tty_proc(outbuf, inbuf);
		printf("%s", outbuf);
	}

	close(sockfd);

	return 0;
}
