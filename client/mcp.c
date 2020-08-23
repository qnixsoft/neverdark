#include "mcp.h"

#include <unistd.h>

#include "metal.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
/* #include <stdlib.h> */
#include "tty.h"

#define GET_FLAG(x)	( mcp.flags & x )
#define SET_FLAGS(x)	{ mcp.flags |= x ; }
#define UNSET_FLAGS(x)	( mcp.flags &= ~(x) )

enum mcp_flags {
	MCP_ON = 1,
	MCP_KEY = 2,
	MCP_MULTI = 4,
	MCP_ARG = 8,
	MCP_NOECHO = 16,
	MCP_SKIP = 32,
	MCP_INBAND = 64,

	MCP_NAME = 128,
	MCP_HASH = 256,
};

enum mcp_state {
	// unknown
        // 1 means "\n" was read from telnet
        // 2 means "\n#"
        // 3 means "\n#$" and confirms mcp
	MCP_CONFIRMED = 4,
};

struct mcp_arg {
        char key[32];
        char value[1024];
};

struct {
	int state, flags;
        struct mcp_arg args[8];
        int args_l;
	char name[32];
	char cache[2048], *cache_p;
} mcp;

static char in_buf[4096];
static char out_buf[8282];
char *out_p, *last_p;

static inline void mcp_set(char *buf) {
	/* *mcp.cache_p = '\0'; */
	memcpy(buf, mcp.cache, sizeof(mcp.cache));
	memset(mcp.cache, 0, sizeof(mcp.cache));
	mcp.cache_p = mcp.cache;
}

static inline void mcp_clear() {
	memset(mcp.args, 0, sizeof(mcp.args));
	memset(mcp.name, 0, sizeof(mcp.name));
	memset(mcp.cache, 0, sizeof(mcp.cache));
	mcp.args_l = 0;
	mcp.cache_p = mcp.cache;
	mcp.flags = 0;
	mcp.state = 1;
}

static void mcp_emit() {
	struct mcp_arg *arg;
	out_p += sprintf(out_p, "{ \"key\": \"%s\"", mcp.name);
	for (arg = mcp.args; arg < &mcp.args[mcp.args_l]; arg++) {
		out_p += sprintf(out_p, ", \"%s\": \"", arg->key);
		out_p += tty_proc(out_p, arg->value);
		*out_p ++ = '"';
	}
	out_p += sprintf(out_p, " }, ");
	last_p = out_p - 2;
	mcp_clear();
}

static void inband_emit() {
	if (*mcp.cache) {
		out_p += sprintf(out_p,
				"{ \"key\": \"inband\","
				" \"data\": \"");
		out_p += tty_proc(out_p, mcp.cache);
		/* out_p += sprintf(out_p, "%s", mcp.cache); */
		out_p += sprintf(out_p, "\" }, ");
		last_p = out_p - 2;
	}
	
	mcp_clear();
}

static inline struct mcp_arg *
mcp_arg() {
	return &mcp.args[mcp.args_l];
}

#include "package.h"

int wsfd;

/* extern void output(char *); */

static inline int
pkg_handle(char *buf) {
	pkg_head_t head;
	read(wsfd, &head, sizeof(head));
	switch (head.flags) {
	case PKG_INBAND: {
		char raw[BUFSIZ];
		char tty[2 * BUFSIZ];
		read(wsfd, raw, head.len);
		tty_proc(tty, raw);
		/* output(tty); */
	}
	}
	return 0;
}

export char *
mcp_proc() {
	char *in;

        for (in = in_buf; in;)
		in = pkg_handle(in);

	return NULL;
}

export char *
mcp_input() {
	return in_buf;
}

export void
mcp_reset() {
	last_p = out_p = out_buf;
	*out_p++ = '[';
	*out_p = '\0';
}

export void
mcp_init() {
        mcp.state = 1;
	mcp_reset();
}
