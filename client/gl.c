#include "tty.h"

struct glcolor {
	float r, g, b;
} glCol[] = {
	{ .0, .0, .0 },
	{ .75, .0, .0 },
	{ .0, .75, .0 },
	{ .75, .75, .0 },
	{ .0, .0, .75 },
	{ .75, .0, .75 },
	{ .0, .75, .75 },
	{ .75, .75, .75 },

	{ .25, .25, .25 },
	{ 1., .0, .0 },
	{ .0, 1., .0 },
	{ 1., 1., .0 },
	{ .0, .0, 1. },
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

	fifo->type = type;
	fifo->item = item;
}

void
gl_csic_fg(struct tty *tty) {
	union gl_tty_item item = { .fg = &glCol[tty->csi.fg] };
	gl_tty_append(tty, GLIT_FG, item);
}

void
gl_csic_bg(struct tty *tty) {
	union gl_tty_item item = { .bg = &glCol[tty->csi.bg] };
	gl_tty_append(tty, GLIT_BG, item);
}

void
gl_csic_end(struct tty *tty) {
	union gl_tty_item fgi = { .fg = &glCol[7] };
	union gl_tty_item bgi = { .bg = &glCol[0] };
	gl_tty_append(tty, GLIT_FG, fgi);
	gl_tty_append(tty, GLIT_BG, bgi);
}

void
gl_echo(struct tty *tty, char ch) {
	union gl_tty_item item = { .ch = ch };
	gl_tty_append(tty, GLIT_CHAR, item);
}

static void
gl_init(struct tty *tty) {
	struct gl_tty_payload *pl = malloc(sizeof(struct gl_tty_payload));
	pl->first = NULL;
	pl->last = NULL;
	tty->driver.payload = pl;
}

struct tty_driver gl_tty_driver = {
	.csic_pre = &csic_nothing,
	.csic_start = &csic_nothing,
	.csic_fg = &gl_csic_fg,
	.csic_bg = &gl_csic_bg,
	.csic_end = &gl_csic_end,
	.csic_nil = &buf_csic_nil,
	.flush = &buf_flush,
	.echo = &gl_echo,
	.init = &gl_init,
};

