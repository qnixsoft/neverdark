/* $Header: */

/*
 * This file includes the logic needed to parse the start of a database file and
 * determine whether it is old or new format, has old or new compression, etc.
 *
 * Needed because olddecomp.c suddenly gets a lot more complicated when we
 * have to handle all the modern formats.
 *
 * It contains the minimum amount of smarts needed to read this without
 * having to link in everything else.
 *
*/

#include "copyright.h"
#include "config.h"

#include <string.h>

#include "db_header.h"
#include "params.h"

static int
do_peek(FILE * f)
{
	int peekch;

	ungetc((peekch = getc(f)), f);

	return (peekch);
}

dbref
getref(FILE * f)
{
	static char buf[BUFFER_LEN];
	int peekch;

	/*
	 * Compiled in with or without timestamps, Sep 1, 1990 by Fuzzy, added to
	 * Muck by Kinomon.  Thanks Kino!
	 */
	if ((peekch = do_peek(f)) == NUMBER_TOKEN || peekch == LOOKUP_TOKEN) {
		return (0);
	}
	fgets(buf, sizeof(buf), f);
	return (atol(buf));
}

static char xyzzybuf[BUFFER_LEN];
const char *
getstring_noalloc(FILE * f)
{
	char *p;
	char c;

	if (fgets(xyzzybuf, sizeof(xyzzybuf), f) == NULL) {
		xyzzybuf[0] = '\0';
		return xyzzybuf;
	}

	if (strlen(xyzzybuf) == BUFFER_LEN - 1) {
		/* ignore whatever comes after */
		if (xyzzybuf[BUFFER_LEN - 2] != '\n')
			while ((c = fgetc(f)) != '\n') ;
	}
	for (p = xyzzybuf; *p; p++) {
		if (*p == '\n') {
			*p = '\0';
			break;
		}
	}

	return xyzzybuf;
}


int
db_read_header( FILE *f, const char **version, int *load_format, dbref *grow, int *parmcnt )
{
	int result = 0;
	int grow_and_dbflags = 0;
	const char *special;
	char c;

	/* null out the putputs */
	*version = NULL;
	*load_format = 0;
	*grow = 0;
	*parmcnt = 0;

	/* if the db doesn't start with a * it is incredibly ancient and has no header */
	/* this routine can deal with - just return */	
	c = getc( f );
	ungetc( c, f );
	
	/* read the first line to id it */
	special = getstring_noalloc( f );

	/* save whatever the version string was */
	/* NOTE: This only works because we only do getstring_noalloc once */
	result |= DB_ID_VERSIONSTRING;
	*version = special;

	*load_format = 11;
	grow_and_dbflags = TRUE;

	/* All recent versions could have these */
	if ( grow_and_dbflags ) {
		int dbflags;

		*grow = getref(f);
		result |= DB_ID_GROW;

		dbflags = getref(f);
	}

	return result;
}
