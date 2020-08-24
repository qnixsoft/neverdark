#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/select.h>
#include <errno.h>
#include <string.h>
#include <curses.h>
#include "tty.h"

#define FIXEDSTR(a) a, (sizeof(a) + 1)

int
main(int argc, char *argv[], char *envp[])
{
	int sockfd, n; 
	struct sockaddr_in servaddr; 
	char inbuf[2 * BUFSIZ];
	char outbuf[4 * BUFSIZ];
	char username[64];
	char password[64];
	struct timeval tv;
	fd_set rd;

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

	fprintf(stderr, "Username: ");
	scanf("%s", username);
	fprintf(stderr, "Password: ");
	initscr();
	noecho();
	scanf("%s", password);
	echo();
	endwin();

	setvbuf(stdin, NULL, _IOLBF, 0);
	setvbuf(stdout, NULL, _IOLBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	n = snprintf(inbuf, sizeof(inbuf), "auth %s %s", username, password);
	write(sockfd, inbuf, n + 2); 

	for (;;) {
		FD_ZERO(&rd);
		FD_SET(0, &rd);
		FD_SET(sockfd, &rd);
		tv.tv_sec = 120;
		tv.tv_usec = 0;
		n = select(sockfd + 1, &rd, 0, 0, &tv);
		if (n < 0) {
			if (errno == EINTR)
				continue;
			perror("select");
		} else if (n == 0) {
			perror("0 on select");
		} else if (FD_ISSET(sockfd, &rd)) {
			ssize_t ret = read(sockfd, inbuf, sizeof(inbuf));
			if (ret < 0) {
				if (errno == EINTR)
					continue;
				perror("read");
				break;
			}
			else if (ret == 0)
				continue;
			inbuf[ret] = '\0';
			tty_proc(outbuf, inbuf);
			printf("%s", outbuf);
		} else if (FD_ISSET(0, &rd)) {
			char *ptr = fgets(inbuf, sizeof(inbuf), stdin);
			if (ptr == NULL)
				perror("fgets");
			write(sockfd, ptr, strlen(ptr) + 1);
		}

	}

	close(sockfd);

	return 0;
}
