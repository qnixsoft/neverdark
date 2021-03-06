#ifndef _DEFAULTS_H
#define _DEFAULTS_H

/* #define MUD_ID "www" */

#define DUMPWARN_MESG   "## Game will pause to save the database in a few minutes. ##"
#define DELTAWARN_MESG  "## Game will pause to save changed objects in a few minutes. ##"
#define DUMPDELTAS_MESG "## Saving changed objects ##"
#define DUMPING_MESG    "## Pausing to save database. This may take a while. ##"
#define DUMPDONE_MESG   "## Save complete. ##"


/* Change this to the name of your muck.  ie: FurryMUCK, or Tapestries */
#define MUCKNAME "NeverDark"

/* name of the monetary unit being used */
#define PENNY "penny"
#define PENNIES "pennies"
#define CPENNY "Penny"
#define CPENNIES "Pennies"

/* message seen when a player enters a line the server doesn't understand */
#define HUH_MESSAGE "Huh?  (Type \"help\" for help.)"

/*  Goodbye message.  */
#define LEAVE_MESSAGE "Come back later!"

/*  Idleboot message.  */
#define IDLEBOOT_MESSAGE "Autodisconnecting for inactivity."

/*  How long someone can idle for.  */
#define MAXIDLE TIME_HOUR(2)

/*  Boot idle players?  */
#define IDLEBOOT 1

/* ping anti-idle time in seconds - just under 1 minute NAT timeout */
#define IDLE_PING_TIME 55

/* Limit max number of players to allow connected?  (wizards are immune) */
#define PLAYERMAX 0

/* How many connections before blocking? */
#define PLAYERMAX_LIMIT 56

/* The mesg to warn users that nonwizzes can't connect due to connect limits */
#define PLAYERMAX_WARNMESG "You likely won't be able to connect right now, since too many players are online."

/* The mesg to display when booting a connection because of connect limit */
#define PLAYERMAX_BOOTMESG "Sorry, but there are too many players online.  Please try reconnecting in a few minutes."

/*
 * Message if someone trys the create command and your system is
 * setup for registration.
 */
#define REG_MSG "Sorry, you can get a character by e-mailing XXXX@machine.net.address with a charname and password."

/* command to run when entering a room. */
#define AUTOLOOK_CMD "look"

/* Format of standardized property lists. */
#define PROPLIST_INT_COUNTER 1	/* Specifies that the proplist counter
				   property should be stored as an integer
				   property instead of as a string. */

#define PROPLIST_COUNTER_FORMAT "P#"	/* The prop that has the count of lines. */
									 /* Define as empty string for no counter. */
									 /* P substitutes the proplist name */
									 /* All other chars are literal. */

#define PROPLIST_ENTRY_FORMAT "P#/N"	/* The props that contain the list data. */
									 /* P substitutes the proplist name */
									 /* N substitutes the item number */
									 /* All other chars are literal. */

/* various times */
#define AGING_TIME TIME_DAY(90)	/* Unused time before obj shows as old. */
#define DUMP_INTERVAL TIME_HOUR(4)	/* time between dumps (or deltas) */
#define CLEAN_INTERVAL TIME_MINUTE(15)	/* time between unused obj purges */


/* amount of object endowment, based on cost */
#define MAX_OBJECT_ENDOWMENT 100

/* Block various penny-related functions at less than given mucker level. */
/* 1 = M1, 2 = M2, 3 = M3, 4 = Wiz */
#define MOVEPENNIES_MUF_MLEV 2
#define ADDPENNIES_MUF_MLEV 2
/* This define affects the {money:} MPI function as well. */
#define PENNIES_MUF_MLEV 1

/* minimum costs for various things */
#define OBJECT_COST 10			/* Amount it costs to make an object    */
#define EXIT_COST 1				/* Amount it costs to make an exit      */
#define LINK_COST 1				/* Amount it costs to make a link       */
#define ROOM_COST 80			/* Amount it costs to dig a room        */
#define LOOKUP_COST 0			/* cost to do a scan                    */
#define MAX_PENNIES 10000		/* amount at which temple gets cheap    */
#define PENNY_RATE 0			/* 1/chance of getting a penny per room */
#define START_PENNIES 50		/* # of pennies a player's created with */

/* FREE_FRAMES_POOL is the number of program frames that are always
 *  available without having to allocate them.  Helps prevent memory
 *  fragmentation.
 */
#define FREE_FRAMES_POOL 8

#define PLAYER_START ((dbref) 208)	/* room number of player start location */

/* Server support of @doing (reads the _/do prop on WHOs) */
#define WHO_DOING 1

/* run an m3 exit with the commandline being the parameter on HUH */
#define M3_HUH 0

/* clear out unused programs every so often */

/* Makes WHO unavailable before connecting to a player, or when Interactive.
 * This lets you prevent bypassing of a global @who program. */
#define SECURE_WHO 0

/* Makes all items under the environment of a room set Wizard, be controlled
 * by the owner of that room, as well as by the object owner, and Wizards. */
#define REALMS_CONTROL 0

/* Allows 'listeners' (see CHANGES file) */
#define LISTENERS 0

/* Forbid listener programs of less than given mucker level. 4 = wiz */
#define LISTEN_MLEV 3

/* Allows listeners to be placed on objects. */
#define LISTENERS_OBJ 1

/* Searches up the room environments for listeners */
#define LISTENERS_ENV 1

/* Minimum mucker level to write to the userlog. 4 = wiz */
#define USERLOG_MLEV 3

/* Allow mortal players to @force around objects that are set ZOMBIE. */
#define ZOMBIES 1

/* Allow only wizards to @set the VEHICLE flag on Thing objects. */
#define WIZ_VEHICLES 0

/* Force Mucker Level 1 muf progs to prepend names on notify's to players
 * other than the using player, and on notify_except's and notify_excludes. */
#define FORCE_MLEV1_NAME_NOTIFY 1
/* Define these to let players set TYPE_THING and TYPE_EXIT objects dark. */
#define EXIT_DARKING 1
#define THING_DARKING 1

/* Define this to 1 to make sleeping players effectively DARK */
#define DARK_SLEEPERS 0

/* Define this to 1 if you want DARK players to not show up on the WHO list
 * for mortals, in addition to not showing them in the room contents. */
#define WHO_HIDES_DARK 1

/* Allow a player to use teleport-to-player destinations for exits */
#define TELEPORT_TO_PLAYER 1

/* Make using a personal action require that the source room
 * be controlled by the player, or else be set JUMP_OK */
#define SECURE_TELEPORT 0

/* Is MPI's {istype} and {type} command set to be lazy permission?  1 = yes */
#define LAZY_MPI_ISTYPE_PERM 0

/* Allow MUF to perform bytecode optimizations. */
#define OPTIMIZE_MUF 1

/* force MUF comments to use strict oldstyle, and not allow recursion. */
#define MUF_COMMENTS_STRICT 1

/* Enable or diable the global 'HOME' command. */
#define ALLOW_HOME 1

/* Enable or disable the server's ability to 'skip' rooms in the environment */
/* chain when trying to match a player's exit or command request.  Turning */
/* this on allows the 'Y'ield and 'O'vert flags to function on things or */
/* rooms, changing the way in which command or exit names are found. */
#define ENABLE_MATCH_YIELD 0

/* Enable or disable triggering of movement propqueues when any type of */
/* object moves, not just objects set ZOMBIE or VEHICLE.  This can vastly */
/* increase the amount of processing done, but does allow servers to be */
/* able to programmatically track all movement, so people can't MPI force */
/* an object past a lock, then set it Z or V on the other side. */
#define SECURE_THING_MOVEMENT 0

/* With this defined to 1, exits that aren't on TYPE_THING objects will */
/* always act as if they have at least a Priority Level of 1.  */
/* Define this if you want to use this server with an old db, and don't want */
/* to re-set the Levels of all the LOOK, DISCONNECT, and CONNECT actions. */
#define COMPATIBLE_PRIORITIES 1

/* Only allow killing people with the Kill_OK bit. */
#define RESTRICT_KILL 1

/* Define to 1 to allow _look/ propqueue hooks. */
#define LOOK_PROPQUEUES 0

/* Define to 1 to allow locks to check down the environment for props. */
#define LOCK_ENVCHECK 0

/* Define to 0 to prevent diskbasing of property values, or to 1 to allow. */
#define DISKBASE_PROPVALS 1

/* Define to 1 to cause muf debug tracing to display expanded arrays. */
#define EXPANDED_DEBUG_TRACE 1

/* Specifies the maximum number of timers allowed per process. */
#define PROCESS_TIMER_LIMIT 4

/* Log commands that take longer than this many milliseconds */
#define CMD_LOG_THRESHOLD_MSEC 1000

/* max. amount of queued output in bytes, before you get <output flushed> */
#define MAX_OUTPUT 131071

/* Flags that new players will be created with. */
#define PCREATE_FLAGS "C"

/* Smatch pattern of names that cannot be used. */
#define RESERVED_NAMES ""

/* Smatch pattern of player names that cannot be used. */
#define RESERVED_PLAYER_NAMES ""

/* Enable support for ignoring players */
#define IGNORE_SUPPORT 1

/* Enable bidirectional ignoring for players */
#define IGNORE_BIDIRECTIONAL 1

/* Verbose @clone command. */
#define VERBOSE_CLONE 0

/* Force 7-bit names */
#if 1 /* ASCII_THING_NAMES */
#define OK_ASCII_THING(name) 1
#define OK_ASCII_OTHER(name) ok_ascii_any(name)
#else
#define OK_ASCII_THING(name) ok_ascii_any(name)
#define OK_ASCII_OTHER(name) 1
#endif

#endif /* _DEFAULTS_H */

#ifdef DEFINE_HEADER_VERSIONS

#ifndef defaultsh_version
#define defaultsh_version
const char *defaults_h_version = "$RCSfile$ $Revision: 1.34 $";
#endif
#else
extern const char *defaults_h_version;
#endif

