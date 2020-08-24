#include "tty.h"

#include <stdio.h>
#include <ctype.h>

struct attr {
        int fg, bg, x;
};

struct tty;

typedef ssize_t tty_csi_change_cb(struct tty *, char *out);
typedef void tty_csi_nil_cb(struct tty *);

struct tty {
	int flags;
        int esc_state, csi_changed;
        struct attr c_attr, csi;
	tty_csi_change_cb *csic_pre, *csic_start,
			  *csic_fg, *csic_bg, *csic_end;
	tty_csi_nil_cb *csic_nil;
	char *end_tag;
};

ssize_t
web_csic_pre(struct tty *tty, char *out) {
        return sprintf(out, "%s", tty->end_tag);
}

ssize_t
web_csic_start(struct tty *tty, char *out) {
	return sprintf(out, "<span class=\\\"");
}

ssize_t
web_csic_fg(struct tty *tty, char *out) {
	return sprintf(out, "cf%d", tty->csi.fg);
}

ssize_t
web_csic_bg(struct tty *tty, char *out) {
	return sprintf(out, " c%d", tty->csi.bg);
}

ssize_t
web_csic_end(struct tty *tty, char *out) {
	ssize_t ret = sprintf(out, "\\\">");
	tty->end_tag = "</span>";
	return ret;
}

void
web_csic_nil(struct tty *tty) {
	tty->end_tag = "";
}

ssize_t
tee_csic_nothing(struct tty *tty, char *out) {
	return 0;
}

ssize_t
tee_csic_fg(struct tty *tty, char *out) {
	char *fout = out;
	int fg = tty->csi.fg;
	if (fg >= 8) {
		out += sprintf(out, "\x1b[1m");
		fg -= 8;
	}
	out += sprintf(out, "\x1b[%dm", fg + 30);
	return out - fout;
}

ssize_t
tee_csic_bg(struct tty *tty, char *out) {
	return sprintf(out, "\x1b[%dm", tty->csi.bg + 40);
}

ssize_t
tee_csic_end(struct tty *tty, char *out) {
	tty->end_tag = "\x1b[0m";
	return 0;
}

static inline void
params_push(struct tty *tty, int x)
{
	int     fg = tty->c_attr.fg,
		bg = tty->c_attr.bg;

	switch (x) {
	case 0: fg = 7; bg = 0; break;
	case 1: fg += 8; break;
	default: if (x >= 40)
			 bg = x - 40;
		 else if (x >= 30)
			 fg = (fg >= 8 ? 8 : 0) + x - 30;
	}

	tty->csi.fg = fg;
	tty->csi.bg = bg;
	tty->csi.x = x;
}

static inline size_t
csi_change(char *out, struct tty *tty)
{
	char *fout = out;
	int a = tty->csi.fg != 7, b = tty->csi.bg != 0;
	out += tty->csic_pre(tty, out);

	if (a || b) {
		out += tty->csic_start(tty, out);
		if (a)
			out += tty->csic_fg(tty, out);
		if (b)
			out += tty->csic_bg(tty, out);

		out += tty->csic_end(tty, out);
	} else
		tty->csic_nil(tty);

        return out - fout;
}

void tty_init(struct tty *tty) {
	tty->csi.fg = tty->c_attr.fg = 7;
	tty->csi.bg = tty->c_attr.bg = 0;
	tty->csi.x = tty->c_attr.x = 0;
        tty->end_tag = "";
	tty->esc_state = 0;
	tty->csic_pre = &web_csic_pre;
	/* tty->csic_pre = &tee_csic_nothing; */
	/* tty->csic_start = &web_csic_start; */
	tty->csic_start = &tee_csic_nothing;
	/* tty->csic_fg = &web_csic_fg; */
	tty->csic_fg = &tee_csic_fg;
	/* tty->csic_bg = &web_csic_bg; */
	tty->csic_bg = &tee_csic_bg;
	/* tty->csic_end = &web_csic_end; */
	tty->csic_end = &tee_csic_end;
	tty->csic_nil = &web_csic_nil;
}

char *escape_map[256] = {
	[ 0 ... 255 ] = "",
	/* [(unsigned) '\n'] = "\\n", */
	[(unsigned) '\t'] = "\\t",
	[(unsigned) '"'] = "\\\"",
	[(unsigned) '\\'] = "\\\\",
	[(unsigned) '/'] = "\\/",
};

static inline size_t
esc_state_0(char *out, struct tty *tty, unsigned char ch) {
	char *fout = out;

	if (tty->csi_changed) {
		out += csi_change(out, tty);
		tty->csi_changed = 0;
	}

	if (*escape_map[(unsigned) ch] != '\0')
		out += sprintf(out, "%s", escape_map[(int) ch]);
	else
		*out++ = ch;

	return out - fout;
}

static inline size_t
tty_proc_ch(char *out, struct tty *tty, char *p) {
	register char ch = *p;

	switch (ch) {
	case '\x18':
	case '\x1a':
		tty->esc_state = 0;
		return 0;
	case '\x1b':
		tty->esc_state = 1;
		return 0;
	case '\x9b':
		tty->esc_state = 2;
		return 0;
	case '\x07': 
	case '\x00':
	case '\x7f':
	case '\v':
	case '\r':
	case '\f':
		return 0;
	}

	switch (tty->esc_state) {
	case 0:
		return esc_state_0(out, tty, ch);
	case 1:
		switch (ch) {
		case '[':
			tty->esc_state = 2;
			break;
		case '=':
		case '>':
		case 'H':
			tty->esc_state = 0; /* IGNORED */
		}
		break;
	case 2: // just saw CSI
		switch (ch) {
		case 'K':
		case 'H':
		case 'J':
			tty->esc_state = 0;
			return 0;
		case '?':
			tty->esc_state = 5;
			return 0;
		}
		params_push(tty, 0);
		tty->esc_state = 3;
	case 3: // saw CSI and parameters
		switch (ch) {
		case 'm':
			if (tty->c_attr.bg != tty->csi.bg
			    || tty->c_attr.fg != tty->csi.fg)
			{
				tty->c_attr.fg = tty->csi.fg;
				tty->c_attr.bg = tty->csi.bg;
				tty->c_attr.x = 0;
				tty->csi.x = 0;
				tty->csi_changed = 1;
			}
			tty->esc_state = 0;
			break;
		case '[':
			tty->esc_state = 4;
			break;
		case ';':
			params_push(tty, 0);
			break;
		default:
			if (ch >= '0' && ch <= '9')
				params_push(tty, tty->csi.x * 10 + (ch - '0'));
			else
				tty->esc_state = 0;
		}
		break;

	case 5: params_push(tty, ch);
		tty->esc_state = 6;
		break;
	case 4:
	case 6: tty->esc_state = 0;
		break;
	}

	return 0;
}

size_t
tty_proc(char *out, char *input) {
        struct tty tty;
	char *in, *fout = out;

        tty_init(&tty);
        for (in = input; *in != '\0'; in++)
		out += tty_proc_ch(out, &tty, in);
	out += tty.csic_pre(&tty, out);
	*out++ = '\0';

        return out - fout;
}
