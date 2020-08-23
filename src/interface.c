/* $Header$ */

/* Copyright 1992-2001 by Fuzzball Software */
/* Consider this code protected under the GNU public license, with explicit
 * permission to distribute when linked against openSSL. */

#define DEFINE_HEADER_VERSIONS
#include "fb.h"
#undef DEFINE_HEADER_VERSIONS
#include "copyright.h"
#include "config.h"
#include "match.h"
#include "mpi.h"
#include "web.h"

#include <sys/types.h>

#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

# define NEED_SOCKLEN_T
//"do not include netinet6/in6.h directly, include netinet/in.h.  see RFC2553"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <openssl/ssl.h>

#include "db.h"
#include "interface.h"
#include "command.h"
#include "params.h"
#include "defaults.h"
#include "props.h"
#include "externs.h"
#include "interp.h"
#include "kill.h"
#include "search.h"
#include "view.h"
#include "geography.h"
#include "item.h"
#include "mob.h"
#undef NDEBUG
#include "debug.h"
#include "noise.h"
#include "ws.h"

#define DESCR_ITER(di_d) \
	for (di_d = &descr_map[sockfd + 1]; \
	     di_d < &descr_map[FD_SETSIZE]; \
	     di_d++) \
		if (!FD_ISSET(di_d->fd, &activefds) \
		    || !(di_d->flags & DF_CONNECTED)) \
			continue; \
		else

enum descr_flags {
	DF_CONNECTED = 1,
	DF_BOOTED = 2,
	DF_WEBSOCKET = 4,
};

struct ws {
	int flags;
	unsigned ip;
	unsigned old;
};

#define QUEUE_MAX (BUFSIZ << 3)

typedef struct {
	char buf[QUEUE_MAX], *p;
	ssize_t len;
} queue_t;

typedef struct descr_st {
	int fd, flags;
	int con_number;
	dbref player;
	struct {
		queue_t input, output;
	} inband;
	struct ws ws;
	long connected_at;
	/* int quota; */
} descr_t;

core_command_t *cmds_hashed[254] = {
	[ 0 ... 253 ] = NULL,
};

extern void do_auth(command_t *cmd);
extern void do_httpget(command_t *cmd);

core_command_t cmds[] = {
	{
		.name = "auth",
		.cb = &do_auth,
		.flags = CF_NOAUTH,
	}, {
		.name = "GET",
		.cb = &do_httpget,
		.flags = CF_NOAUTH,
	}, {
		.name = "action",
		.cb = &do_action,
	}, {
		.name = "advitam",
		.cb = &do_advitam,
	}, {
		.name = "attach",
		.cb = &do_attach,
	}, {
		.name = "bless",
		.cb = &do_bless,
	}, {
		.name = "boot",
		.cb = &do_boot,
	}, {
		.name = "chlock",
		.cb = &do_chlock,
	}, {
		.name = "chown",
		.cb = &do_chown,
	}, {
		.name = "chlock",
		.cb = &do_chlock,
	}, {
		.name = "clone",
		.cb = &do_clone,
	}, {
		.name = "conlock",
		.cb = &do_conlock,
	}, {
		.name = "contents",
		.cb = &do_contents,
	}, {
		.name = "create",
		.cb = &do_create,
	}, {
		.name = "credits",
		.cb = &do_credits,
	}, {
		.name = "describe",
		.cb = &do_describe,
	}, {
		.name = "dig",
		.cb = &do_dig,
	/* }, { */
	/* 	.name = "doing", */
	/* 	.cb = &do_doing, */
	}, {
		.name = "drop_message",
		.cb = &do_drop_message,
	/* }, { */
	/* 	.name = "dump", */
	/* 	.cb = &do_dump, */
	}, {
		.name = "entrances",
		.cb = &do_entrances,

		/* sane_dump_object(player, arg1); /1* examine *1/ */
	}, {
		.name = "fail",
		.cb = &do_fail,
	}, {
		.name = "find",
		.cb = &do_find,
	}, {
		.name = "flock",
		.cb = &do_flock,
	/* }, { */
	/* 	.name = "force", */
	/* 	.cb = &do_force, */
	}, {
		.name = "flock",
		.cb = &do_flock,
	}, {
		.name = "heal",
		.cb = &do_heal,
	}, {
		.name = "idescribe",
		.cb = &do_idescribe,
	}, {
		.name = "link",
		.cb = &do_link,
	}, {
		.name = "lock",
		.cb = &do_lock,
	}, {
		.name = "name",
		.cb = &do_name,
	}, {
		.name = "newpassword",
		.cb = &do_newpassword,
	}, {
		.name = "odrop",
		.cb = &do_odrop,
	}, {
		.name = "oecho",
		.cb = &do_oecho,
	/* }, { */
	/* 	.name = "ofail", */
	/* 	.cb = &do_ofail, */
	}, {
		.name = "open",
		.cb = &do_open,
	}, {
		.name = "osuccess",
		.cb = &do_osuccess,
	}, {
		.name = "owned",
		.cb = &do_owned,
	}, {
		.name = "password",
		.cb = &do_password,
	}, {
		.name = "pcreate",
		.cb = &do_pcreate,
	}, {
		.name = "pecho",
		.cb = &do_pecho,
	}, {
		.name = "propset",
		.cb = &do_propset,
	}, {
		.name = "recycle",
		.cb = &do_recycle,
	}, {
		.name = "relink",
		.cb = &do_relink,
	/* }, { */
	/* 	.name = "restrict", */
	/* 	.cb = &do_restrict, */
	/* }, { */
		/* sanity(player); */
		/* .name = "command", */
		/* .cb = &do_command, */
		/* sanechange(player, full_command); /1* sanchange *1/ */
	}, {
		/* sanfix(player); */
		.name = "set",
		.cb = &do_set,

		/* do_showextver(player); */
	}, {
		.name = "shutdown",
		.cb = &do_shutdown,
	}, {
		.name = "stats",
		.cb = &do_stats,
	}, {
		.name = "success",
		.cb = &do_success,
	}, {
		.name = "sweep",
		.cb = &do_sweep,
	}, {
		.name = "teleport",
		.cb = &do_teleport,
	}, {
		.name = "toad",
		.cb = &do_toad,
	}, {
		.name = "trace",
		.cb = &do_trace,
	}, {
		.name = "unbless",
		.cb = &do_unbless,
	}, {
		.name = "unlink",
		.cb = &do_unlink,
	}, {
		.name = "unlock",
		.cb = &do_unlock,
	}, {
		.name = "usage",
		.cb = &do_usage,
	}, {
		.name = "version",
		.cb = &do_version,
	}, {
		.name = "wall",
		.cb = &do_wall,
	}, {
		.name = "buy",
		.cb = &do_buy,
	}, {
		.name = "leave",
		.cb = &do_leave,
	}, {
		.name = "drink",
		.cb = &do_drink,
	}, {
		.name = "drop",
		.cb = &do_drop,
	}, {
		.name = "eat",
		.cb = &do_eat,
	}, {
		.name = "examine",
		.cb = &do_examine,
	}, {
		.name = "equip",
		.cb = &do_equip,
	}, {
		.name = "fill",
		.cb = &do_fill,
	}, {
		.name = "get",
		.cb = &do_get,
	}, {
		.name = "give",
		.cb = &do_give,
	}, {
		.name = "gripe",
		.cb = &do_gripe,
	}, {
		.name = "help",
		.cb = &do_help,
	}, {
		.name = "inventory",
		.cb = &do_inventory,
	}, {
		.name = "info",
		.cb = &do_info,
	}, {
		.name = "kill",
		.cb = &do_kill,
	}, {
		.name = "look_at",
		.cb = &do_look_at,
	/* }, { */
	/* 	.name = "move", */
	/* 	.cb = &do_move, */
	/* 	/1* do_move(descr, player, arg1, 0); *1/ */
	/* }, { */
	/* 	.name = "motd", */
	/* 	.cb = &do_motd, */
	/* 	/1* /2* do_motd(player, full_command); *2/ *1/ */
	}, {
		.name = "view",
		.cb = &do_view,
	/* }, { */
	/* 	.name = "meme", */
	/* 	.cb = &do_meme, */
	/* 	/1* /2* do_meme(descr, player, arg1); *2/ *1/ */
	}, {
		.name = "man",
		.cb = &do_man,
	}, {
		.name = "news",
		.cb = &do_news,
	}, {
		.name = "page",
		.cb = &do_page,
	}, {
		.name = "pose",
		.cb = &do_pose,
	}, {
		.name = "rob",
		.cb = &do_rob,
	}, {
		.name = "say",
		.flags = CF_EOL,
		.cb = &do_say,
	}, {
		.name = "score",
		.cb = &do_score,
	}, {
		.name = "sell",
		.cb = &do_sell,
	}, {
		.name = "select",
		.cb = &do_select,
	}, {
		.name = "shop",
		.cb = &do_shop,
	}, {
		.name = "sit",
		.cb = &do_sit,
	}, {
		.name = "stand",
		.cb = &do_stand,
	}, {
		.name = "status",
		.cb = &do_status,
	}, {
		.name = "train",
		.cb = &do_train,
	}, {
		.name = "unequip",
		.cb = &do_unequip,
	}, {
		.name = "whisper",
		.cb = &do_whisper,
	},
};

fd_set activefds, readfds, writefds;
descr_t *descriptor_list = NULL;

#define MAX_LISTEN_SOCKS 16

int shutdown_flag = 0;

static const char *create_fail =
		"Either there is already a player with that name, or that name is illegal.\r\n";

static int sockfd;
descr_t descr_map[FD_SETSIZE];

int shovechars();
void close_sockets(const char *msg);
void    remember_player_descr(dbref player, int);
int*    get_player_descrs(dbref player, int* count);
void    forget_player_descr(dbref player, int);
descr_t * descrdata_by_descr(int i);

void
command_debug(command_t *cmd, char *label)
{
	char **arg;

	warn("command_debug '%s' %d", label, cmd->argc);
	for (arg = cmd->argv;
	     arg < cmd->argv + cmd->argc;
	     arg++)
	{
		warn(" '%s'", *arg);
	}
	warn("\n");
}

void
announce_puppets(dbref player, const char *msg, const char *prop)
{
	dbref what, where;
	const char *ptr, *msg2;
	char buf[BUFFER_LEN];

	for (what = 0; what < db_top; what++) {
		if (Typeof(what) == TYPE_THING && (FLAGS(what) & ZOMBIE)) {
			if (OWNER(what) == player) {
				where = getloc(what);
				if ((!Dark(where)) && (!Dark(player)) && (!Dark(what))) {
					msg2 = msg;
					if ((ptr = (char *) get_property_class(what, prop)) && *ptr)
						msg2 = ptr;
					snprintf(buf, sizeof(buf), "%.512s %.3000s", NAME(what), msg2);
					notify_except(DBFETCH(where)->contents, what, buf, what);
				}
			}
		}
	}
}

static inline void
announce_disconnect(descr_t *d)
{
	command_t cmd = command_new_null(d->fd, d->player);
	dbref player = d->player;
	dbref loc;
	char buf[BUFFER_LEN];

	if ((loc = getloc(player)) == NOTHING)
		return;

	if ((!Dark(player)) && (!Dark(loc))) {
		snprintf(buf, sizeof(buf), "%s has disconnected.", NAME(player));
		notify_except(DBFETCH(loc)->contents, player, buf, player);
	}

	/* trigger local disconnect action */
	if (PLAYER_DESCRCOUNT(player) == 1) {
		if (can_move(&cmd, "disconnect", 1))
			go_move(&cmd, "disconnect", 1);
		announce_puppets(player, "falls asleep.", "_/pdcon");
	}

	d->flags = 0;
	d->player = NOTHING;

	forget_player_descr(player, d->fd);

	/* queue up all _connect programs referred to by properties */
	envpropqueue(&cmd, getloc(player), NOTHING, player, NOTHING,
				 "_disconnect", "Disconnect", 1, 1);
	envpropqueue(&cmd, getloc(player), NOTHING, player, NOTHING,
				 "_odisconnect", "Odisconnect", 1, 0);

	ts_lastuseobject(player);
	DBDIRTY(player);
}

int
descr_close(descr_t *d)
{
	if (d->flags & DF_CONNECTED) {
		warn("%d disconnects\n", d->fd);
		announce_disconnect(d);
	} else
		warn("%d never connected\n", d->fd);

	FD_CLR(d->fd, &activefds);
	shutdown(d->fd, 2);
	int ret = close(d->fd);
	memset(d, 0, sizeof(descr_t));
	return ret;
}

static inline command_t
command_new(descr_t *d, char *input, size_t len)
{
	command_t cmd;
	register char *p = input;

	p[len] = '\0';
	cmd.player = d->player;
	cmd.fd = d->fd;
	cmd.argc = 0;

	if (!*p || !isprint(*p)) {
		descr_close(d);
		return cmd;
	}

	cmd.argv[0] = p;
	cmd.argc++;

	for (; p < input + len; p++) {
		if (*p == '\r')
			break;

		if (!isprint(*p)) {
			memset(&cmd, 0, sizeof(cmd));
			descr_close(d);
			return cmd;
		}

		if (*p != ' ')
			continue;

		*p = '\0';

		cmd.argv[cmd.argc] = p + 1;
		cmd.argc ++;
	}

	*p = '\0';

	for (int i = cmd.argc;
	     i < sizeof(cmd.argv) / sizeof(char *);
	     i++)

		cmd.argv[i] = "";

	cmd.argv[cmd.argc] = p + 1;

	command_debug(&cmd, "init");
	return cmd;
}

static inline int
command_idx(command_t *cmd)
{
	noise_t h = uhash(cmd->argv[0], strlen(cmd->argv[0]), 88);
	return h & 0xff;
}

static inline core_command_t *
command_match(command_t *cmd) {
	core_command_t *cc = cmds_hashed[command_idx(cmd)];
	char *a, *b;

	if (!cc)
		return NULL;

	for (a = cc->name, b = cmd->argv[0];
	     *a && *b; a++, b++)
		if (*a != *b)
			return NULL;

	return cc;
}

command_t command_null(command_t *cmd) {
	command_t ret;
	ret.player = cmd->player;
	ret.fd = cmd->fd;
	ret.argc = 0;
	memset(ret.argv, '0', sizeof(ret.argv));
	return ret;
}

command_t command_new_null(int descr, ref_t player) {
	command_t ret;
	command_null(&ret);
	ret.player = player;
	ret.fd = descr;
	return ret;
}

static inline void
commands_init() {
	int i;

	for (i = 0; i < sizeof(cmds) / sizeof(core_command_t); i++) {
		const char *name = cmds[i].name;
		noise_t h = uhash((void *) name, strlen(name), 88);
		int idx = h & 0xff;
		if (cmds_hashed[idx] != NULL)
			warn("%s collides with %s\n", name, cmds_hashed[idx]->name);
		cmds_hashed[idx] = &cmds[i];
	}
}

short optflags = 0;
pid_t global_dumper_pid=0;
short global_dumpdone=0;

void
show_program_usage(char *prog)
{
	fprintf(stderr, "Usage: %s [-sSyWv?] [-C [path]]", prog);
	fprintf(stderr, "    Options:\n");
	fprintf(stderr, "        -C PATH   changes directory to PATH before starting up.\n");
	fprintf(stderr, "        -S        don't do db sanity checks at startup time.\n");
	fprintf(stderr, "        -s        load db, then enter the interactive sanity editor.\n");
	fprintf(stderr, "        -y        attempt to auto-fix a corrupt db after loading.\n");
	fprintf(stderr, "        -W        only allow wizards to login.\n");
	fprintf(stderr, "        -v        display this server's version.\n");
	fprintf(stderr, "        -?        display this message.\n");
	exit(1);
}

/* NOTE: Will need to think about this more for unicode */
#define isinput( q ) isprint( (q) & 127 )

extern int sanity_violated;

void
close_sockets(const char *msg) {
	descr_t *d;

	DESCR_ITER(d) {
		forget_player_descr(d->player, d->fd);
		if (shutdown(d->fd, 2) < 0)
			perror("shutdown");
		close(d->fd);
	}
}

int
main(int argc, char **argv)
{
	register char c;

	memset(descr_map, 0, sizeof(descr_map));

	while ((c = getopt(argc, argv, "dsyvSC:")) != -1) {
		switch (c) {
		case 'd':
			optflags |= OPT_DETACH;
			break;
		case 's':
			optflags |= OPT_SANITY_INTERACTIVE;
			break;
		case 'S':
			optflags |= OPT_NOSANITY;
			break;
		case 'y':
			optflags |= OPT_SANITY_AUTOFIX;
			break;
		case 'v':
			printf("%s\n", VERSION);
			break;
			
		case 'C':
			if (chdir(optarg)) {
				perror("chdir");
				return 4;
			}
			break;
		default:
			show_program_usage(*argv);
			return 1;

		case '?':
			show_program_usage(*argv);
			return 0;
		}
	}

	warn("INIT: TinyMUCK %s starting.\n", "version");
	warn("%s PID is: %d\n", argv[0], getpid());

	if (init_game() < 0) {
		warn("Couldn't load " STD_DB "!\n");
		return 2;
	}

	CBUG(map_init());
	commands_init();

	set_signals();

	sanity(AMBIGUOUS);
	errno = 0; // TODO why? sanity fails to access file

	if (sanity_violated) {
		optflags |= OPT_WIZONLY;
		if (optflags & OPT_SANITY_AUTOFIX)
			sanfix(AMBIGUOUS);
	}

	if (shovechars())
		return 1;

	map_close();
	mob_save();

	close_sockets("\r\nServer shutting down.\r\n");

	dump_database();

	return 0;
}

int notify_nolisten_level = 0;

/* static inline int */
/* descr_write(descr_t *d, const char *data, size_t len) */
/* { */
/* 	if (d->flags & DF_WEBSOCKET) */
/* 		return ws_write(d->fd, data, len); */
/* 	else */
/* 		return write(d->fd, data, len); */

/* #if 0 */
/* 	if (d->inband.output.p < d->inband.output.buf + QUEUE_MAX) { */
/* 		memcpy(d->inband.output.p, data, len); */
/* 		d->inband.output.len += len; */
/* 		return len; */
/* 	} */

/* 	return -1; */
/* #endif */
/* } */


#include "package.h"

int
descr_inband(descr_t *d, const char *s)
{
	size_t len = strlen(s);
	/* return descr_write(d, s, strlen(s)); */
	if (d->flags & DF_WEBSOCKET) {
		package_t pkg;
		pkg.head.flags = PKG_INBAND;
		pkg.head.len = len;
		memcpy(pkg.data, s, len);
		return ws_write(d->fd, &pkg, sizeof(pkg_head_t) + len);
	}
	else
		return write(d->fd, s, len);
}

typedef struct {
	descr_t *d;
	int *darr, dcount, di;
} pdi_t;

#define PLAYER_DESCR_ITER(pdi, player) \
    pdi.darr = get_player_descrs(player, &pdi.dcount); \
    for (pdi.di = 0; pdi.di < pdi.dcount; pdi.di++) \
	    if ((pdi.d = descrdata_by_descr(pdi.darr[pdi.di])))

static inline int
player_inband(dbref player, char *buf)
{
	pdi_t pdi;

	PLAYER_DESCR_ITER(pdi, player)
		descr_inband(pdi.d, buf);

	return pdi.dcount;
}

int
notify_nolisten(dbref player, const char *msg, int isprivate)
{
	int retval = 0;
	char buf[BUFFER_LEN + 2];
	char buf2[BUFFER_LEN + 2];
	int firstpass = 1;
	char *ptr1;
	const char *ptr2;
	dbref ref;

	ptr2 = msg;
	while (ptr2 && *ptr2) {
		ptr1 = buf;
		while (ptr2 && *ptr2 && *ptr2 != '\r')
			*(ptr1++) = *(ptr2++);
		*(ptr1++) = '\r';
		*(ptr1++) = '\n';
		*(ptr1++) = '\0';
		if (*ptr2 == '\r')
			ptr2++;

		if (firstpass)
			retval += player_inband(player, buf);

#if ZOMBIES
		if ((Typeof(player) == TYPE_THING) && (FLAGS(player) & ZOMBIE) &&
		    !(FLAGS(OWNER(player)) & ZOMBIE) &&
		    (!(FLAGS(player) & DARK) || Wizard(OWNER(player)))) {
			ref = getloc(player);
			if (Wizard(OWNER(player)) || ref == NOTHING ||
			    Typeof(ref) != TYPE_ROOM || !(FLAGS(ref) & ZOMBIE)) {
				if (isprivate || getloc(player) != getloc(OWNER(player))) {
					command_t cmd_pp = command_new_null(-1, player);
					char pbuf[BUFFER_LEN];
					const char *prefix;
					char ch = *match_args;

					*match_args = '\0';

					if (notify_nolisten_level <= 0)
					{
						notify_nolisten_level++;

						prefix = do_parse_prop(&cmd_pp, player, MESGPROP_PECHO, "(@Pecho)", pbuf, sizeof(pbuf), MPI_ISPRIVATE);

						notify_nolisten_level--;
					}
					else
						prefix = 0;

					*match_args = ch;

					if (!prefix || !*prefix) {
						prefix = NAME(player);
						snprintf(buf2, sizeof(buf2), "%s> %.*s", prefix,
							 (int)(BUFFER_LEN - (strlen(prefix) + 3)), buf);
					} else {
						snprintf(buf2, sizeof(buf2), "%s %.*s", prefix,
							 (int)(BUFFER_LEN - (strlen(prefix) + 2)), buf);
					}

					if (firstpass)
						retval += player_inband(player, buf);
				}
			}
		}
#endif
		firstpass = 0;
	}
	return retval;
}

int
notify_filtered(dbref from, dbref player, const char *msg, int isprivate)
{
	if (msg == 0)
		return 0;
	return notify_nolisten(player, msg, isprivate);
}

int
notify_from_echo(dbref from, dbref player, const char *msg, int isprivate)
{

#if LISTENERS
	const char *ptr=msg;
#if !LISTENERS_OBJ
	if (Typeof(player) == TYPE_ROOM)
#endif
		listenqueue(-1, from, getloc(from), player, player, NOTHING,
			    "_listen", ptr, LISTEN_MLEV, 1, 0);
	listenqueue(-1, from, getloc(from), player, player, NOTHING,
		    "~listen", ptr, LISTEN_MLEV, 1, 1);
	listenqueue(-1, from, getloc(from), player, player, NOTHING,
		    "~olisten", ptr, LISTEN_MLEV, 0, 1);
#endif

	dbref ref;

	if (!(Typeof(player) == TYPE_THING && (FLAGS(player) & VEHICLE) &&
		(!(FLAGS(player) & DARK) || Wizard(OWNER(player)))))

		goto out;

	ref = getloc(player);

	if (!(Wizard(OWNER(player)) || ref == NOTHING ||
	    Typeof(ref) != TYPE_ROOM || !(FLAGS(ref) & VEHICLE)
	   ) || isprivate || getloc(from != getloc(player)))

		goto out;

	char buf[BUFFER_LEN];
	char pbuf[BUFFER_LEN];
	const char *prefix;
	char ch = *match_args;
	command_t cmd_pp = command_new_null(-1, from);

	*match_args = '\0';
	prefix = do_parse_prop(&cmd_pp, player, MESGPROP_OECHO, "(@Oecho)", pbuf, sizeof(pbuf), MPI_ISPRIVATE);
	*match_args = ch;

	if (!prefix || !*prefix)
		prefix = "Outside>";

	snprintf(buf, sizeof(buf), "%s %.*s", prefix, (int)(BUFFER_LEN - (strlen(prefix) + 2)), msg);

	ref = DBFETCH(player)->contents;
	while (ref != NOTHING) {
		notify_filtered(from, ref, buf, isprivate);
		ref = DBFETCH(ref)->next;
	}

out:
	return notify_filtered(from, player, msg, isprivate);
}

int
notify_from(dbref from, dbref player, const char *msg)
{
	return notify_from_echo(from, player, msg, 1);
}

int
notify(dbref player, const char *msg)
{
	return notify_from_echo(player, player, msg, 1);
}

void
notify_fmt(dbref player, char *format, ...)
{
	va_list args;
	char bufr[BUFFER_LEN];

	va_start(args, format);
	vsnprintf(bufr, sizeof(bufr), format, args);
	bufr[sizeof(bufr)-1] = '\0';
	notify(player, bufr);
	va_end(args);
}

struct timeval
timeval_sub(struct timeval now, struct timeval then)
{
	now.tv_sec -= then.tv_sec;
	now.tv_usec -= then.tv_usec;
	if (now.tv_usec < 0) {
		now.tv_usec += 1000000;
		now.tv_sec--;
	}
	return now;
}

int
msec_diff(struct timeval now, struct timeval then)
{
	return ((now.tv_sec - then.tv_sec) * 1000 + (now.tv_usec - then.tv_usec) / 1000);
}

extern void purge_free_frames(void);

static void
do_tick()
{
	mob_update();
	geo_update();
}

void
wall(const char *msg)
{
	descr_t *d;
	char buf[BUFSIZ];

	strlcpy(buf, msg, sizeof(buf));
	strlcat(buf, "\r\n", sizeof(buf));

	DESCR_ITER(d) descr_inband(d, buf);
}

int
queue_read(descr_t *d, queue_t *q) {
	int ret = read(d->fd, q->p, QUEUE_MAX - q->len);
	/* warn("queue_read pre %d %d %p\n", ret, d->fd, (void *) d); */
	if (ret <= 0)
		return ret;

	if (ret < 2)
		return -2;

	ret -= 2;
	q->len += ret;
	*(q->p = q->buf + q->len) = '\0';
	ret ++;
	/* warn("queue_read %d %ld bytes %ld+%d/%d -- %s\n", d->fd, q->len, q->len - ret, ret, QUEUE_MAX, q->buf); */
	return ret;
}

void
mob_welcome(descr_t *d)
{
	struct obj const *o = mob_obj_random();
	if (o) {
		CBUG(*o->name == '\0');
		descr_inband(d, o->name);
		descr_inband(d, "\r\n\r\n");
		/* art(d->fd, o->art); */
                if (*o->description) {
                        if (*o->description != '\0')
                                descr_inband(d, o->description);
                        descr_inband(d, "\r\n\r\n");
                }
	}
}

void
welcome_user(descr_t *d)
{
	FILE *f;
	char *ptr;
	char buf[BUFFER_LEN];

        /* if (!web_support(d->fd)) { */
                if ((f = fopen(WELC_FILE, "rb")) == NULL) {
                        descr_inband(d, DEFAULT_WELCOME_MESSAGE);
                        perror("spit_file: welcome.txt");
                } else {
                        while (fgets(buf, sizeof(buf) - 3, f)) {
                                ptr = index(buf, '\n');
                                if (ptr && ptr > buf && *(ptr - 1) != '\r') {
                                        *ptr++ = '\r';
                                        *ptr++ = '\n';
                                        *ptr++ = '\0';
                                }
                                descr_inband(d, buf);
                        }
                        fclose(f);
                }
        /* } */

        mob_welcome(d);

	if (optflags & OPT_WIZONLY) {
		descr_inband(d, "## The game is currently in maintenance mode, and only wizards will be able to connect.\r\n");
	}
#if PLAYERMAX
	else if (con_players_curr >= PLAYERMAX_LIMIT) {
		if (PLAYERMAX_WARNMESG && *PLAYERMAX_WARNMESG) {
			descr_inband(d, PLAYERMAX_WARNMESG);
			descr_inband(d, "\r\n");
		}
	}
#endif
}

void
announce_connect(command_t *cmd)
{
	dbref player = cmd->player;
	dbref loc;
	char buf[BUFFER_LEN];
	struct match_data md;
	dbref exit;

	if ((loc = getloc(player)) == NOTHING)
		return;

	if ((!Dark(player)) && (!Dark(loc))) {
		snprintf(buf, sizeof(buf), "%s has connected.", NAME(player));
		notify_except(DBFETCH(loc)->contents, player, buf, player);
	}

	exit = NOTHING;
	if (PLAYER_DESCRCOUNT(player)) {
		init_match(cmd, "connect", TYPE_EXIT, &md);	/* match for connect */
		md.match_level = 1;
		match_all_exits(&md);
		exit = match_result(&md);
		if (exit == AMBIGUOUS)
			exit = NOTHING;
	}

	if (exit == NOTHING || !(FLAGS(exit) & STICKY)) {
		if (can_move(cmd, AUTOLOOK_CMD, 1))
			go_move(cmd, AUTOLOOK_CMD, 1);
		else
			do_look_around(cmd);
	}

	/*
	 * See if there's a connect action.  If so, and the player is the first to
	 * connect, send the player through it.  If the connect action is set
	 * sticky, then suppress the normal look-around.
	 */

	if (exit != NOTHING)
		go_move(cmd, "connect", 1);

	if (PLAYER_DESCRCOUNT(player) == 1) {
		announce_puppets(player, "wakes up.", "_/pcon");
	}

	/* queue up all _connect programs referred to by properties */
	envpropqueue(cmd, getloc(player), NOTHING, player, NOTHING,
				 "_connect", "Connect", 1, 1);
	envpropqueue(cmd, getloc(player), NOTHING, player, NOTHING,
				 "_oconnect", "Oconnect", 1, 0);

	ts_useobject(player);
	return;
}

void
do_httpget(command_t *cmd)
{
	descr_t *d = descrdata_by_descr(cmd->fd);
	ws_handshake(cmd->fd, cmd->argv[cmd->argc]);
	d->flags |= DF_WEBSOCKET;
}

void
do_auth(command_t *cmd)
{
	int descr = cmd->fd;
	char *user = cmd->argv[1];
	char *password = cmd->argv[2];
        int created = 0;
        dbref player = connect_player(user, password);
	descr_t *d = descrdata_by_descr(descr);

        if ((optflags & OPT_WIZONLY) && !TrueWizard(player)) {
                descr_inband(d, (optflags & OPT_WIZONLY)
                           ? "Sorry, but the game is in maintenance mode currently, and "
                           "only wizards are allowed to connect.  Try again later."
                           : PLAYERMAX_BOOTMESG);
                descr_inband(d, "\r\n");
		d->flags |= DF_BOOTED;
		return;
        }

        if (player == NOTHING) {
                player = create_player(user, password);

                if (player == NOTHING) {
                        descr_inband(d, create_fail);
                        /* if (d->proto.ws.ip) */
                        /*         web_logout(d->fd); */

                        warn("FAILED CREATE %s on fd %d\n", user, d->fd);
			return;
                }

                warn("CREATED %s(%d) on fd %d\n",
                           NAME(player), player, d->fd);
                created = 1;
        } else
                warn("CONNECTED: %s(%d) on fd %d\n",
                           NAME(player), player, d->fd);
        d->flags |= DF_CONNECTED;
        d->connected_at = time(NULL);
        cmd->player = d->player = player;
        remember_player_descr(player, d->fd);
        /* cks: someone has to initialize this somewhere. */
        /* PLAYER_SET_BLOCK(d->player, 0); */
        /* welcome_user(d); */
        spit_file(player, MOTD_FILE);
        announce_connect(cmd);
        if (created) {
                /* TODO do_help(player, "begin", ""); */
                mob_put(player);
        } else {
                if (sanity_violated && Wizard(player))
                        notify(player,
                               "#########################################################################\n"
                               "## WARNING!  The DB appears to be corrupt!  Please repair immediately! ##\n"
                               "#########################################################################");
        }
        /* if (!(web_support(d->fd) && d->proto.ws.old)) */
	do_view(cmd);
        look_room(cmd, getloc(player), 0);

	return;
}

static inline int
do_v(command_t *cmd, char const *cmdstr)
{
	int ofs = 1;
	char const *s = cmdstr;

	for (; *s && ofs > 0; s += ofs) {
		switch (*s) {
		case COMMAND_TOKEN:
			return s - cmdstr;
		/* case SAY_TOKEN: */
		/* 	do_say(player, s + 1); */
		/* 	return s + strlen(s) - cmd; */
		/* case POSE_TOKEN: */
		/* 	do_pose(player, s + 1); */
		/* 	return s + strlen(s) - cmd; */
		}

		ofs = geo_v(cmd, s);
		if (ofs < 0)
			ofs = - ofs;
		s += ofs;
		ofs = kill_v(cmd, s);
	}

	return s - cmdstr;
}

static inline void
command_process(command_t *cmd)
{
	if (cmd->argc < 1) {
		return;
	}

	char *command = cmd->argv[0];
	size_t command_n = 0;
	dbref player = cmd->player;
	int descr = cmd->fd;

	/* command_debug(cmd, "command_process"); */
	/* warn("command_process %s\n", command); */

	/* robustify player */
	if (player >= 0 && (player >= db_top ||
	    (Typeof(player) != TYPE_PLAYER && Typeof(player) != TYPE_THING))) {
		warn("process_command: bad player %d", player);
		return;
	}

        // set current descriptor (needed for death)
	if (player >= 0) {
		pos_t pos;
		map_where(pos, getloc(cmd->player));

		CBUG(GETLID(player) < 0);
		mobi_t *liv = MOBI(player);
		liv->descr = descr;

		/* if player is a wizard, and uses overide token to start line... */
		/* ... then do NOT run actions, but run the command they specify. */
		if (!(TrueWizard(OWNER(player)) && (*command == OVERIDE_TOKEN))
		    && can_move(cmd, command, 0))
		{
			go_move(cmd, command, 0);	/* command is exact match for exit */
			*match_args = 0;
			*match_cmdname = 0;
			goto out;
		}

		for (; command_n < cmd->argc; command_n ++)
		{
			command = cmd->argv[command_n];
			core_command_t *cmd_i = command_match(cmd);

			if (cmd_i) {
				if ((cmd_i->flags & CF_EOL)) {
					char buf[BUFSIZ];
					char *p = buf;
					int i;
					for (i = 1; i <= cmd->argc ; i++)
						p += sprintf(p, "%s ", cmd->argv[i]);
					*(p - 2) = '\0';
					cmd->argv[1] = buf;
					cmd_i->cb(cmd);
				} else
					cmd_i->cb(cmd);
				break;
			}

			int matched;
			command += do_v(cmd, command);
			if (*command == COMMAND_TOKEN) {
				command++;
				matched = 1;
				CBUG(1);
			} else if (*command == '\0') {
				continue;
			} else
				break;
			/* goto bad; */
		}
out:
		{
			pos_t pos2;
			map_where(pos2, getloc(player));
			if (MORTON_READ(pos2) != MORTON_READ(pos))
				do_view(cmd);
		}
	} else {
		core_command_t *cmd_i = command_match(cmd);

		if (cmd_i && (cmd_i->flags & CF_NOAUTH))
			cmd_i->cb(cmd);
	}

}

static inline void
descr_process(descr_t *d, char *input, size_t input_len)
{
	/* warn("descr_process %d\n", d->fd); */

	command_t cmd = command_new(d, input, input_len);

	if (!cmd.argc)
		return;

	command_process(&cmd);
}

static inline void
queue_init(queue_t *q)
{
	q->p = q->buf;
	q->len = 0;
}

static inline descr_t *
descr_new()
{
	descr_t *d;
	struct sockaddr_in addr;
	socklen_t addr_len;
	int fd;

	addr_len = (socklen_t)sizeof(addr);
	fd = accept(sockfd, (struct sockaddr *) &addr, &addr_len);

	warn("descr_new %d %s\n", fd, inet_ntoa(addr.sin_addr));

	/* FIXME */
	if (fd <= 0) {
		perror("descr_new");
		return NULL;
	}

	d = &descr_map[fd];
	memset(d, 0, sizeof(descr_t));

	d->fd = fd;


	FD_SET(d->fd, &activefds);

	d->player = -1;
	d->connected_at = time(NULL);

	if (fcntl(d->fd, F_SETFL, O_NONBLOCK) == -1) {
		perror("make_nonblocking: fcntl");
		panic("O_NONBLOCK fcntl failed");
	}

	return d;
}

static inline int
make_socket(int port)
{
	int opt;
	struct sockaddr_in server;
	int fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);

	if (fd < 0) {
		perror("socket");
		return -1;
	}

	opt = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof(opt)) < 0) {
		perror("setsockopt");
		return -1;
	}

	opt = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *) &opt, sizeof(opt)) < 0) {
		perror("setsockopt");
		return -1;
	}

	/*
	opt = 240;
	if (setsockopt(fd, SOL_TCP, TCP_KEEPIDLE, (char *) &opt, sizeof(opt)) < 0) {
		perror("setsockopt");
		exit(1);
	}
	*/

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	if (bind(fd, (struct sockaddr *) &server, sizeof(server))) {
		perror("bind");
		close(fd);
		return -1;
	}

	FD_SET(fd, &activefds);

	listen(fd, 5);
	return fd;
}

static inline int
descr_read(descr_t *d)
{

	if (d->flags & DF_WEBSOCKET) {
		char buf[BUFSIZ];
		ssize_t len = ws_read(d->fd, buf, sizeof(buf));
		switch (len) {
		case -1:
			if (errno == EAGAIN)
				return 0;

			perror("descr_read ws ");
		case 0: return -1;
		}
		descr_process(d, buf, len);
		/* warn("ws_read %lld\n", len); */
		return len;
	} else {
		queue_t *q = &d->inband.input;
		queue_init(q);
		switch (queue_read(d, q)) {
		case -1:
			if (errno == EAGAIN)
				return 0;

			perror("descr_read");
			return -1;
		case 0: return -1;
		}
		descr_process(d, q->buf, q->len);
		return q->len;
	}
}

int
shovechars()
{
	time_t now;
	struct timeval timeout;
	descr_t *d;
	int avail_descriptors, i;

	FD_ZERO(&activefds);
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);

	sockfd = make_socket(TINYPORT);

	if (sockfd <= 0) {
		perror("make_socket");
		return sockfd;
	}

	descr_map[sockfd].fd = sockfd;

	/* warn("shovechars %d\n", sockfd); */

	avail_descriptors = sysconf(_SC_OPEN_MAX) - 5;

	(void) time(&now);

	mob_init();

	/* Daemonize */
	if ((optflags & OPT_DETACH) && daemon(1, 1) != 0)
		_exit(0);

/* And here, we do the actual player-interaction loop */

	while (shutdown_flag == 0) {
		/* process_commands(); */
		do_tick();

		DESCR_ITER(d)
			if (d->flags & DF_BOOTED) {
				descr_inband(d, "\r\n" LEAVE_MESSAGE "\r\n\r\n");
				d->flags ^= DF_BOOTED;
				descr_close(d);
			}

		if (global_dumpdone != 0) {
			wall(DUMPING_MESG);
			global_dumpdone = 0;
		}
		purge_free_frames();
		untouchprops_incremental(1);

		if (shutdown_flag)
			break;

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		readfds = activefds;
		int select_n = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);

		switch (select_n) {
		case -1:
			switch (errno) {
			case EAGAIN:
				return 0;
			case EINTR:
				continue;
			}

			perror("select");
			return -1;
		case 0:
			continue;
		}

		/* warn("select_n %d\n", select_n); */

		/* TODO iterate using minfd */
		for (d = descr_map, i = 0;
		     d < descr_map + FD_SETSIZE;
		     d++, i++) {
			if (!FD_ISSET(i, &readfds))
				continue;

			if (i == sockfd) {
				descr_new();
			} else if (descr_read(d) < 0)
				descr_close(d);
		}
	}

	/* End of the player processing loop */

	(void) time(&now);
	add_property((dbref) 0, "_sys/lastdumptime", NULL, (int) now);
	add_property((dbref) 0, "_sys/shutdowntime", NULL, (int) now);
	return 0;
}

void
wall_wizards(const char *msg)
{
	descr_t *d;
	char buf[BUFFER_LEN + 2];

	strlcpy(buf, msg, sizeof(buf));
	strlcat(buf, "\r\n", sizeof(buf));

	DESCR_ITER(d)
		if (Wizard(d->player))
			descr_inband(d, buf);
}

int
boot_off(dbref player)
{
	pdi_t pdi;

	PLAYER_DESCR_ITER(pdi, player) {
		pdi.d->flags |= DF_BOOTED;
		descr_close(pdi.d);
	}

	return !pdi.dcount;
}

void
boot_player_off(dbref player)
{
	pdi_t pdi;

	PLAYER_DESCR_ITER(pdi, player)
		pdi.d->flags = DF_BOOTED;
}

void
emergency_shutdown(void)
{
	close_sockets("\r\nEmergency shutdown due to server crash.");
}

void
dump_users(descr_t *e, char *user)
{
	descr_t *d;
	int wizard;
	time_t now;
	char buf[2048];
	char pbuf[64];
	char secchar = ' ';

	wizard = (e->flags & DF_CONNECTED) && Wizard(e->player);

	while (*user && (isspace(*user) || *user == '*'))
		user++;

	if (wizard)
		/* S/he is connected and not quelled. Okay; log it. */
		warn("WIZ: %s(%d) in %s(%d):  %s", NAME(e->player),
					(int) e->player, NAME(DBFETCH(e->player)->location),
					(int) DBFETCH(e->player)->location, "WHO");

	if (!*user)
		user = NULL;

	(void) time(&now);
	if (wizard) {
		descr_inband(e, "Player Name                Location     On For Idle   Host\r\n");
	} else {
		descr_inband(e, "Player Name           On For Idle\r\n");
	}

	DESCR_ITER(d) if ((
			   !WHO_HIDES_DARK || wizard
			   || !(FLAGS(d->player) & DARK))
			  && (!user || string_prefix(NAME(d->player), user))) {

		secchar = ' ';

		if (wizard) {
			/* don't print flags, to save space */
			snprintf(pbuf, sizeof(pbuf), "%.*s(#%d)", PLAYER_NAME_LIMIT + 1,
				 NAME(d->player), (int) d->player);
			snprintf(buf, sizeof(buf),
				 "%-*s [%6d] %c%c\r\n",
				 PLAYER_NAME_LIMIT + 10, pbuf,
				 (int) DBFETCH(d->player)->location,
				 ((FLAGS(d->player) & INTERACTIVE) ? '*' : ' '),
				 secchar);
		} else {
			snprintf(buf, sizeof(buf), "%-*s %c%c\r\n",
				 (int)(PLAYER_NAME_LIMIT + 1),
				 NAME(d->player),
				 ((FLAGS(d->player) & INTERACTIVE) ? '*' : ' '),
				 secchar);
		}
	}

	descr_inband(e, buf);
}

/***** O(1) Connection Optimizations *****/

int*
get_player_descrs(dbref player, int* count)
{
	int* darr;

	if (Typeof(player) == TYPE_PLAYER) {
		*count = PLAYER_DESCRCOUNT(player);
	    darr = PLAYER_DESCRS(player);
		if (!darr) {
			*count = 0;
		}
		return darr;
	} else {
		*count = 0;
		return NULL;
	}
}

void
remember_player_descr(dbref player, int descr)
{
	int  count = 0;
	int* arr   = NULL;

	if (Typeof(player) != TYPE_PLAYER)
		return;

	count = PLAYER_DESCRCOUNT(player);
	arr = PLAYER_DESCRS(player);

	if (!arr) {
		arr = (int*)malloc(sizeof(int));
		arr[0] = descr;
		count = 1;
	} else {
		arr = (int*)realloc(arr,sizeof(int) * (count+1));
		arr[count] = descr;
		count++;
	}
	PLAYER_SET_DESCRCOUNT(player, count);
	PLAYER_SET_DESCRS(player, arr);
}

void
forget_player_descr(dbref player, int descr)
{
	int  count = 0;
	int* arr   = NULL;

	if (Typeof(player) != TYPE_PLAYER)
		return;

	count = PLAYER_DESCRCOUNT(player);
	arr = PLAYER_DESCRS(player);

	if (!arr) {
		count = 0;
	} else if (count > 1) {
		int src, dest;
		for (src = dest = 0; src < count; src++) {
			if (arr[src] != descr) {
				if (src != dest) {
					arr[dest] = arr[src];
				}
				dest++;
			}
		}
		if (dest != count) {
			count = dest;
			arr = (int*)realloc(arr,sizeof(int) * count);
		}
	} else {
		free((void*)arr);
		arr = NULL;
		count = 0;
	}
	PLAYER_SET_DESCRCOUNT(player, count);
	PLAYER_SET_DESCRS(player, arr);
}

descr_t *
descrdata_by_descr(int c)
{
	if (c >= FD_SETSIZE || c < 0)
		return NULL;
	else
		return &descr_map[c];
}

/*** JME ***/

void
art(int descr, const char *art)
{
	FILE *f;
	char *ptr;
	char buf[BUFFER_LEN];
	descr_t *d;

	if (*art == '/' || strstr(art, "..")
	    || (!(string_prefix(art, "bird/")
		|| string_prefix(art, "fish/")
                || !strchr(art, '/'))))

		return;
	
        d = descrdata_by_descr(descr);

	/* descr_inband(d, "\r\n"); */

        /* if (!web_art(descr, art, buf, sizeof(buf))) */
        /*         return; */

	snprintf(buf, sizeof(buf), "../art/%s.txt", art);

	if ((f = fopen(buf, "rb")) == NULL) 
		return;

	while (fgets(buf, sizeof(buf) - 3, f)) {
		ptr = index(buf, '\n');
		if (ptr && ptr > buf && *(ptr - 1) != '\r') {
			*ptr++ = '\r';
			*ptr++ = '\n';
			*ptr++ = '\0';
		}
		descr_inband(d, buf);
	}

	fclose(f);
	descr_inband(d, "\r\n");
}

void
dump_status(void)
{
	descr_t *d;
	time_t now;
	char buf[BUFFER_LEN];

	(void) time(&now);
	warn("STATUS REPORT:");
	DESCR_ITER(d) snprintf(buf, sizeof(buf),
			       "PLAYING fd %d player %s(%d).\n",
			       d->fd, NAME(d->player), d->player);
}

static const char *interface_c_version = "$RCSfile$ $Revision: 1.127 $";
const char *get_interface_c_version(void) { return interface_c_version; }
