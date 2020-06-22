#ifndef COMMAND_H
#define COMMAND_H

typedef int ref_t;

typedef struct {
	ref_t player;
	int fd, argc;
	char *argv[8];
	/* unsigned char direction; /1* enum exit bitmask *1/ */
} command_t; /* FIXME commandi_t */

typedef void core_command_cb_t(command_t *);

enum command_flags {
	CF_NOAUTH = 1,
	CF_EOL = 2,
};

typedef struct {
	char *name;
	core_command_cb_t *cb;
	int flags;
	/* size_t nargs; */
} core_command_t;

extern core_command_t cmds[];

command_t command_null(command_t *cmd);
command_t command_new_null(int descr, ref_t player);
void command_debug(command_t *cmd, char *label);

#endif
