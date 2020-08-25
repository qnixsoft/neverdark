#include "tty.h"

#include <GL/glut.h>

struct glcolor {
	float r, g, b;
} glCol[] = {
	{ .23, .25, .23 },
	{ .75, .0, .0 },
	{ .23, .37, .28 },
	{ .63, .59, .35 },
	{ .0, .0, .75 },
	{ .75, .0, .75 },
	{ .25, .36, .37 },
	{ .75, .76, .85 },

	{ .25, .25, .25 },
	{ 1., .0, .0 },
	{ .32, .82, .54 },
	{ 1., 1., .0 },
	{ .45, .61, .74 },
	{ 1., .0, 1. },
	{ .0, 1., 1. },
	{ 1., 1., 1. },
};

enum gl_tty_item_type {
	GLIT_CHAR,
	GLIT_FG,
	GLIT_BG,
};

union gl_tty_item {
	struct glcolor *fg, *bg;
	char ch;
};

struct gl_tty_fifo {
	enum gl_tty_item_type type;
	union gl_tty_item item;
	struct gl_tty_fifo *next;
};

struct gl_tty_payload {
	struct gl_tty_fifo *first, *last;
};

void
gl_tty_append(struct tty *tty,
	      enum gl_tty_item_type type,
	      union gl_tty_item item)
{
	struct gl_tty_payload *pl
		= (struct gl_tty_payload *) tty->driver.payload;

	struct gl_tty_fifo *fifo = malloc(sizeof(struct gl_tty_fifo));

	fifo->next = NULL;

	if (pl->last != NULL)
		pl->last->next = fifo;
	else
		pl->first = fifo;

	pl->last = fifo;
	fifo->type = type;
	fifo->item = item;
}

void
gl_csic_fg(struct tty *tty) {
	struct glcolor *c = &glCol[tty->csi.fg];
	/* fprintf(stderr, "tty fg %d (%f, %f, %f)\n", tty->csi.fg, c->r, c->g, c->b); */
	union gl_tty_item item = { .fg = c };
	gl_tty_append(tty, GLIT_FG, item);
}

void
gl_csic_bg(struct tty *tty) {
	union gl_tty_item item = { .bg = &glCol[tty->csi.bg] };
	gl_tty_append(tty, GLIT_BG, item);
}

void
gl_echo(struct tty *tty, char ch) {
	union gl_tty_item item = { .ch = ch };
	gl_tty_append(tty, GLIT_CHAR, item);
}

static void
gl_flush(struct tty *tty) {
}

static void
gl_init(struct tty *tty) {
	struct gl_tty_payload *pl = malloc(sizeof(struct gl_tty_payload));
	pl->first = NULL;
	pl->last = NULL;
	tty->driver.payload = pl;
}

static void
gl_csic_pre(struct tty *tty) {
	union gl_tty_item fgi = { .fg = &glCol[7] };
	union gl_tty_item bgi = { .bg = &glCol[0] };
	gl_tty_append(tty, GLIT_FG, fgi);
	gl_tty_append(tty, GLIT_BG, bgi);
}

struct tty_driver gl_tty_driver = {
	/* .csic_pre = &csic_nothing, */
	.csic_pre = &gl_csic_pre,
	.csic_start = &csic_nothing,
	.csic_fg = &gl_csic_fg,
	.csic_bg = &gl_csic_bg,
	.csic_end = &csic_nothing,
	.csic_nil = &buf_csic_nil,
	.flush = &gl_flush,
	.echo = &gl_echo,
	.init = &gl_init,
};

void
gl_tty_render(struct tty *tty) {
	struct gl_tty_payload *pl
		= (struct gl_tty_payload *) tty->driver.payload;

	struct gl_tty_fifo *fifo = pl->first;
	struct glcolor fg = glCol[7], bg = glCol[0];
	char ch;
	float y = .95;
	float x = -.95;

	for (fifo = pl->first; fifo; fifo = fifo->next) {
		switch (fifo->type) {
		case GLIT_FG:
			fg = *fifo->item.fg;
			break;
		case GLIT_BG:
			bg = *fifo->item.bg;
			break;
		case GLIT_CHAR:
			ch = fifo->item.ch;
			switch (ch) {
			case '\n':
				y -= .03;
				x = -.95;
				glRasterPos3f(-.95, y, 0.);
				break;
			default:
				glColor3f(bg.r, bg.g, bg.b);
				glBegin(GL_QUADS);
				glVertex3f(x + 0.016, y - 0.008, -0.1);
				glVertex3f(x + 0.036, y - 0.008, -0.1);
				glVertex3f(x + 0.036, y + 0.022, -0.1);
				glVertex3f(x + 0.016, y + 0.022, -0.1);
				glEnd();
				glColor3f(fg.r, fg.g, fg.b);

				x += .02;
				glRasterPos3f(x, y, 0.);
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ch);

			}
			continue;
		}
	}
}
