#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
/* #include <metal.h> */
/* #include "mcp.h" */
/* #include "view.h" */

int
main(int argc, char *argv[], char *envp[])
{
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	fprintf(stderr, "Hello err\n");
	fprintf(stdout, "Hello out\n");
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd < 0) {
		perror("socket");
		return -1;
	}

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(4202); 

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) != 0) { 
		perror("connect");
		return -1;
	} 

	return 0;
}
