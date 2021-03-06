/*
 * Copyright (c) 1991-2009 by Fuzzball Software
 * under the GNU Public License
 *
 * Some parts of this code -- in particular the dictionary based compression
 * code is Copyright 1995 by Dragon's Eye Productions
 *
 * Some parts of this code Copyright (c) 1990 Chelsea Dyerman
 * University of California, Berkeley (XCF)
 */

/*
 * This file is generated by mkversion.sh. Any changes made will go away.
 */

#include <sys/time.h>
#include "fb.h"
#include "config.h"
#include "patchlevel.h"
#include "params.h"
#include "externs.h"
#include "version.h"

const char *version = PATCHLEVEL;

const char *infotext[] =
{
    VERSION,
    "",
    HASH,
    DATE,
    " ",
    "Based on the original code written by these programmers:",
    "  David Applegate    James Aspnes    Timothy Freeman    Bennet Yee",
    " ",
    "Others who have done major coding work along the way:",
    "  Lachesis, ChupChups, FireFoot, Russ 'Random' Smith, and Dr. Cat",
    " ",
    "This is a user-extensible, user-programmable multi-user adventure game.",
    "TinyMUCK was derived from TinyMUD v1.5.2, with extensive modifications.",
    "Because of all the modifications, this program is not in any way, shape,",
    "or form being supported by any of the original authors.  Any bugs, ideas,",
    "suggestions,  etc, should be directed to the persons listed below.",
    "Do not send diff files, send us mail about the bug and describe as best",
    "as you can, where you were at when the bug occured, and what you think",
    "caused the bug to be produced, so we can try to reproduce it and track",
    "it down.",
    " ",
    "The following programmers currently maintain the code:",
    "  Winged:        aerowolf@gmail.com  Project Maintainer/Lead Hack",
    "  Foxen/Revar:   revar@belfry.com    Developer",
    "  Points:                            Bug Finder/Lead/Developer",
    " ",
    "The following programmers have contributed greatly:",
    "  Our Sourceforge developers (http://sourceforge.net/projects/fbmuck/):",
    "  Akari, Alynna, Arcticwolf (Schneelocke), Cerilus, Fentonator,",
    "  Ferretbun, Foxbird, Jenora, McClure, Naiya, Natasha O'Brien, Sombre,",
    "  Tiger (Fre'ta), Wog, and WolfWings.",
    " ",
    "The following people helped out a lot along the way:",
    "  Caspian, Kim \"Bookwyrm\" Liu, Chris, Jenora, Lynx, WhiteFire,",
    "  Kimi, Cynbe, Myk, Taldin, Howard, darkfox, Moonchilde, Felorin, Xixia,",
    "  Doran, Riss, King_Claudius, Sarusa@FurryMUCK, and",
    "  Henri@Voregotten Realm.",
    " ",
    "Alpha and beta test sites, who put up with this nonsense:",
    " FB 5-",
    "  HighSeasMUCK, TygryssMUCK, FurryMUCK, CyberFurry, PendorMUCK, Kalasia,",
    "  AnimeMUCK, Realms, FurryII, Tapestries, Unbridled Desires, TruffleMUCK",
    "  and Brazillian Dreams.",
    " FB 6-",
    "  HereLieMonsters, FurrySpaceMUCK, Sol ]|[, and Voregotten Realm.",
    " ",
    "Places silly enough to give Foxen a wizbit at some time or another:",
    "  ChupMuck, HighSeas, TygMUCK, TygMUCK II, Furry, Pendor, Realms,",
    "  Kalasia, Anime, CrossRoadsMUCK, TestMage, MeadowFaire, TruffleMUCK,",
    "  Tapestries, Brazillian Dreams, SocioPolitical Ramifications and more.",
    " ",
    "Thanks also goes to those persons not mentioned here who have added",
    "their advice, opinions, and code to TinyMUCK FB.",
    0,
};


void
do_credits(command_t *cmd)
{
	dbref player = cmd->player;
	int i;

	for (i = 0; infotext[i]; i++)
		notify(player, infotext[i]);
}

void
do_version(command_t *cmd)
{
	dbref player = cmd->player;
	char s[BUFFER_LEN];

	snprintf(s,BUFFER_LEN,"Version: %s Compiled on: %s %s",VERSION,DATE,"");
	notify(player, s);
	return;
}


void
do_showextver(dbref player) {
	notify_nolisten(player, get_array_c_version(), 1);
	notify_nolisten(player, get_boolexp_c_version(), 1);
	notify_nolisten(player, get_copyright_c_version(), 1);
	notify_nolisten(player, get_create_c_version(), 1);
	notify_nolisten(player, get_db_c_version(), 1);
	notify_nolisten(player, get_game_c_version(), 1);
	notify_nolisten(player, get_hashtab_c_version(), 1);
	notify_nolisten(player, get_help_c_version(), 1);
	notify_nolisten(player, get_interface_c_version(), 1);
	notify_nolisten(player, get_interp_c_version(), 1);
	notify_nolisten(player, get_look_c_version(), 1);
	notify_nolisten(player, get_match_c_version(), 1);
	notify_nolisten(player, get_move_c_version(), 1);
	notify_nolisten(player, get_msgparse_c_version(), 1);
	notify_nolisten(player, get_player_c_version(), 1);
	notify_nolisten(player, get_predicates_c_version(), 1);
	notify_nolisten(player, get_propdirs_c_version(), 1);
	notify_nolisten(player, get_property_c_version(), 1);
	notify_nolisten(player, get_props_c_version(), 1);
	notify_nolisten(player, get_random_c_version(), 1);
	notify_nolisten(player, get_rob_c_version(), 1);
	notify_nolisten(player, get_sanity_c_version(), 1);
	notify_nolisten(player, get_set_c_version(), 1);
	notify_nolisten(player, get_signal_c_version(), 1);
	notify_nolisten(player, get_smatch_c_version(), 1);
	notify_nolisten(player, get_speech_c_version(), 1);
	notify_nolisten(player, get_stringutil_c_version(), 1);
	notify_nolisten(player, get_timequeue_c_version(), 1);
	notify_nolisten(player, get_timestamp_c_version(), 1);
	notify_nolisten(player, get_unparse_c_version(), 1);
	notify_nolisten(player, get_utils_c_version(), 1);
	notify_nolisten(player, get_wiz_c_version(), 1);
	notify_nolisten(player, array_h_version, 1);
	notify_nolisten(player, config_h_version, 1);
	notify_nolisten(player, copyright_h_version, 1);
	notify_nolisten(player, db_h_version, 1);
	notify_nolisten(player, dbsearch_h_version, 1);
	notify_nolisten(player, defaults_h_version, 1);
	notify_nolisten(player, externs_auto_h_version, 1);
	notify_nolisten(player, externs_h_version, 1);
	notify_nolisten(player, fb_h_version, 1);
	notify_nolisten(player, fbstrings_h_version, 1);
	notify_nolisten(player, interface_h_version, 1);
	notify_nolisten(player, interp_h_version, 1);
	notify_nolisten(player, match_h_version, 1);
	notify_nolisten(player, mpi_h_version, 1);
	notify_nolisten(player, msgparse_h_version, 1);
	notify_nolisten(player, params_h_version, 1);
	notify_nolisten(player, patchlevel_h_version, 1);
	notify_nolisten(player, props_h_version, 1);
	notify_nolisten(player, smatch_h_version, 1);
	notify_nolisten(player, speech_h_version, 1);
	return;
}

