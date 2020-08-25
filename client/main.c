#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/select.h>
#include <errno.h>
#include <string.h>
#include <curses.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "tty.h"

#define FIXEDSTR(a) a, (sizeof(a) + 1)

Display *display;
Window window, root;
GC gc;
GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo *vi;
Colormap cmap;
XSetWindowAttributes swa;
GLXContext glc;
XWindowAttributes gwa;

void DrawAQuad() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1., 1., -1., 1., 1., 20.);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

	glColor3f(0., 0., 0.);

	char *c;
	glRasterPos3f(-.75, .75, 0.);

	for (c="hello world"; *c != '\0'; c++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
} 

int
main(int argc, char *argv[], char *envp[])
{
	Screen *screen;
	int screenId;
	XEvent ev;
	unsigned long black, white;

	int sockfd, n; 
	struct sockaddr_in servaddr; 
	char inbuf[2 * BUFSIZ];
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

	display = XOpenDisplay(NULL);
	if (display == NULL)
		perror("XOpenDisplay");

	vi = glXChooseVisual(display, 0, att);
	if (vi == NULL)
		perror("glXChooseVisual");

	screen = DefaultScreenOfDisplay(display);
	screenId = DefaultScreen(display);

	root = RootWindowOfScreen(screen);
	cmap = XCreateColormap(display, root, vi->visual, AllocNone);

	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;

	black = BlackPixel(display, screenId);
	white = WhitePixel(display, screenId);

	window = XCreateWindow(display, root, 0, 0, 600, 600,
			       0, vi->depth, InputOutput,
			       vi->visual, CWColormap | CWEventMask, &swa);

	XMapRaised(display, window);
	XStoreName(display, window, "Neverdark client");
	glc = glXCreateContext(display, vi, NULL, GL_TRUE);
	glXMakeCurrent(display, window, glc);

	glEnable(GL_DEPTH_TEST); 
	glutInit(&argc, argv);

	n = snprintf(inbuf, sizeof(inbuf), "auth %s %s", username, password);
	write(sockfd, inbuf, n + 2); 

	struct tty tee_tty, gl_tty;
	tty_init(&tee_tty, tee_tty_driver);
	/* tty_init(&gl_tty, gl_tty_driver); */

	for (;;) {
		while (XPending(display)) {
			XNextEvent(display, &ev);
			XGetWindowAttributes(display, window, &gwa);
			glViewport(0, 0, gwa.width, gwa.height);
			DrawAQuad(); 
			glXSwapBuffers(display, window);
		}

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
			tty_proc(&tee_tty, inbuf);
			/* tty_proc(&gl_tty, inbuf); */
		} else if (FD_ISSET(0, &rd)) {
			char *ptr = fgets(inbuf, sizeof(inbuf), stdin);
			if (ptr == NULL)
				perror("fgets");
			write(sockfd, ptr, strlen(ptr) + 1);
		}

	}

	close(sockfd);
	glXMakeCurrent(display, None, NULL);
	glXDestroyContext(display, glc);
	XDestroyWindow(display, window);
	XFree(screen);
	XCloseDisplay(display);

	return 0;
}
