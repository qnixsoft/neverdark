/* $Header$
 * $Log: params.h,v $
 * Revision 1.8  2002/06/19 07:17:57  revar
 * Added pcreate_flags @tune to specify what flags players are created with.
 * Added and merged Windows specific winfuzz4 changes.
 *
 *
 *
 * 2.2fb6.00rc6
 * Added "objtype" field to results of SYSPARM_ARRAY, for when the sysparm is
 *   of the "dbref" type.  The "objtype" field specifies what type the dbref is
 *   restricted to.
 * Added "label" field to results of SYSPARM_ARRAY, for human readable labels.
 * Added }TELL MUF $define as '} array_make me @ 1 array_make array_notify'
 * Added DEBUGGER_BREAK ( -- ) muf prim.  Forces muf debugger entry/break.
 * Added ABS ( i -- i ) muf prim.  Returns absolute value of integer.
 * Added SIGN ( i -- i ) muf prim.  Returns sign of integer as -1, 0, or 1.
 * Fixed crasher bug with muf process kill while handling mufevent.
 * Fixed bug with GETPIDINFO returning timer event info for a process.
 * Fixed hanging bug in fbmuck init script, when fbmuck errors out.
 * Fixed crasher with GETLINKS primitive.
 * Fixed $author and $note directives to stop them from storing garbage.
 * Fixed crasher bug in ARRAY_FILTER_PROP.
 * Fixed error in ARRAY_FILTER_PROP processing of compressed strings.
 * Fixed error with ANSI reset codes being sent _after_ CRLFs.
 * Fixed crasher bug with null varname in function args declaration.
 * Fixed error in FMTSTRING with accepting negative dynamic precision values.
 * Fixed error in FMTSTRING with accepting a dynamic fieldwidth of -1.
 * Fixed crasher bug in FMTSTRING with dynamic fieldwidths.
 * Changed SSL cert/key load failures to just disable SSL, instead of exiting.
 * Changed SSL cert/key load failure error reporting to show file path/name.
 * Changed commandline to accept -sport with a warning when SSL not supported.
 * Changed makefiles so that 'make install-init' installs SysV init scripts,
 *   instead of 'make install'.  This should help Debian and BSD folks.
 *
 *
 *
 * 2.2fb6.00rc5
 * Added SYSPARM_ARRAY ( str:pattern -- listofdict:sysparminfo ) MUF prim.
 *   Returns a list of dictionaries with info about each @tune parameter that
 *   matches the given smatch wildcard pattern.
 *
 *
 *
 * 2.2fb6.00rc4
 * Changed MUF debugger so it breakpoints just before the program would exit.
 * Changed database format to Foxen7 format, which uses MD5 hashed passwords.
 * Added MUF bytecode optimizer.
 * Added optimize_muf boolean @tune parameter.
 * Added .debug/lastcrashtime human-readable timestamp property for muf crashes.
 * Added color/bold hilighting of muf crashes and backtraces to make them a bit
 *   more readable.
 * Added support for showing original scopevar names in debugging output.
 * Added support for using original scopevar names in debugger.
 * Added sanity check for bad exit link counts.
 * Added -godpasswd option to reset the God character's password.
 * Fixed bug in MCP where _datatag wasn't being preceeded by a separator space.
 * Fixed bad error messages argument numbers in several array_* primitives.
 * Fixed bug where COMPILE state left some values uninitialized.
 * Fixed memory leaks in ARRAY_FMTSTRINGS.
 * Fixed documentation error with ROUND.
 * Fixed issue where user could get charged for @action without action creation.
 * Fixed issue with improper CONCOUNT in status log files.
 * Fixed minor issue where startup INIT message might not display, if status
 *   log is unwritable and DETACH defined.
 * Fixed compile-time bug with inconsistent MALLOC_PROFILING exclusion.
 * Fixed crasher bug in compiling muf with unrecognized words and debug scopedvar
 *   name support.
 * Fixed restart code so that it'll work with newer pid-checking restart scripts.
 * Fixed small non-growing memory leak with dbloaded garbage object names.
 * Fixed crasher bug with letting object names grow near to BUFFER_LEN length.
 * Fixed errors with MUF bytecode localvar fetch-and-clear optimization.
 * Fixed MacOS X portability compile errors with socklen_t.
 *
 *
 *
 * 2.2fb6.00rc3
 * Added ARRAY_FMTSTRINGS ( arr:dicts str:fmt -- list:strs ) MUF prim.  Creates
 *   a formatted string for each dictionary in a list, returning a list of the
 *   formatted strings.
 * Fixed a crasher bug with loading lock props with ARRAY_GET_PROPVALS.
 * Fixed a crasher bug with loading lock props with ARRAY_GET_PROPLIST.
 * Fixed a crasher bug with debug traces of programs with large nested arrays.
 * Changed debug traces to not list out contents of nested arrays.
 * Changed debug traces to not show more than the first 7 items in an array.
 *
 *
 *
 * 2.2fb6.00rc2
 * Fixed crasher bug in new pronoun code.
 * Fixed profiling time and debugging initialization in the FORK muf prim.
 * Added player-based overriding of pronouns via _pronouns/GENDER/%x props.
 *
 *
 *
 * 2.2fb6.00rc1
 * Added MUF $define for }join as '} array_make "" array_join'
 * Added ProgName field to @ps display.
 * Added sie/hir/hirself/etc pronouns for 'herm' and 'hermaphrodite' gender.
 * Added generic gender pronoun support via _pronouns/GENDER/%X props on #0.
 * Added default gender pronoun overrides via _pronouns/_default/%X props on #0.
 * Added ARRAY_SORT_INDEXED muf primitive.  Like ARRAY_SORT, but lets you sort
 *   a list of arrays, based on an indexed element in each.
 * Changed @ps display code to be cleaner.
 * Changed dbdumps to fork() into the background when not using DISKBASEing.
 *
 *
 *
 * 2.2fb6.00b5
 * Removed #ifdefs for FLUSHCHANGES as that code should not be optional.
 * Fixed infinite loop parenting bug.  I think.
 * Fixed a lot of uninitialized struct frame variables in child of FORK.
 * Fixed two-byte buffer overrun in {listprops}
 * Fixed uninitialized program instance count in @prog.
 * Fixed an MCP-GUI crasher bug with programs exiting with live dialogs.
 * Fixed bug #477633: {with:v,{&v},{&v}} displays garbage.
 * Fixed bug #478325: Arrays with 0s for values don't serialize properly.
 * Fixed bug #479093: smatches, array_filter_prop disagree.
 * Fixed bug where FOREGROUND muf progs didn't process MCP messages.
 * Fixed a number of missing MUF primitive documentation sections.
 * Fixed resolver to properly shutdown() indentd sockets.
 * Fixed missing files problem in 'make package'.
 * Fixed sysvinit scripts to not hang if restart script is missing.
 * Changed DESCRSECURE? to be ML3, not wizbit.
 * Changed input quotas to not count MCP messages.
 * Changed command logging to not list null commands.
 * Changed READ to _not_ return blank lines unless the process asked for them.
 * Changed ANSI code handling to use ^[[0m instead of ^[[m at EOL for resetting.
 * Changed dbdump to fork() on DB dump when DISKBASE is not defined.
 * Added 'make distclean'.
 * Added READ_WANTS_BLANKS ( -- ) muf primitive, to indicate the process wants
 *   READ to be able to return blank "" lines.
 * Added new @tune -- default_room_parent. This is the dbref used to parent
 *   rooms as the case of last resort, and defaults to #0 (which was previously
 *   the only thing used). Closes feature request #476091.
 *
 *
 *
 * 2.2fb6.00b4
 * Fixed problem in primitive SETLINK where due to a logic error, objects were
 *   unable to become the 'home' of other objects.  Also allow setlink to now
 *   parent rooms to objects.
 * Fixed problem in primitive NEWOBJECT where due to a logic error, objects were
 *   not valid destinations.
 * Fixed SSL connections that were broken by the MCP flush changes.
 * Fixed garbage char at end of muf DEBUG lines.
 * Fixed bug #205753 -- env-looping problems.
 * Fixed bug #450413 -- Problems with forks within loops.
 * Fixed problem with certain MUF primitives changing an object's last_used
 *   timestamp on content, exit or name check, but not for prop-reading or any
 *   other access.  MUF only updates the last_used timestamp now when the
 *   moveto primitive is used.
 * Fixed permissions problem when both GOD_PRIV and tp_who_doing are set.
 * Fixed bug #424057 -- MATCH and PMATCH primitives now strip ansi sequences
 *   before processing.
 * Fixed _msgmacs searching to allow blessed environment room msgmacs.
 * Fixed bug #233181 -- now DETACH won't if -convert or -insanity is specified
 *   on the commandline.
 * Fixed crasher bug with using undeclared variabled in MPI.
 * Fixed crasher #201633 -- Server now does not crash when program FORCEs
 *   itself to be @recycled.  As a side result of this, there is now another
 *   statuslog line prefix to be aware of: 'SANITYCHECK:'.  If this prefix shows
 *   up in your status log, it generally points to a bug in the code that called
 *   the function that logged the SANITYCHECK:.  Which means, if you see this,
 *   please let us know at http://sourceforge.net/projects/fbmuck/.  Thanks!
 * Fixed a memory leak with using 'var!' in MUF.
 * Fixed interp_loop() based MUF prims to honor TRY-CATCH stack locks.
 * Fixed a bug in GUI_VALUE_SET that checked for 2 args, but popped 3.
 * Fixed arg ordering bug in the REFLIST_* muf primitives.  Now matches docs.
 * Fixed crasher with large arrays, DEBUG output, eith expanded_debug on.
 * Fixed a crasher bug with CLEARing uninitialized variables if CHECKOP fails.
 * Fixed a crasher bug with using '@kill all' when muf timers are present.
 *   This is also the cause of the dequeue_timers() crashes on @shutdown.
 * Fixed MCP GUI to send _closed events for open dlogs, when a descr disconnects.
 * Fixed a couple memory leaks with MCP GUI dialogs.
 * Fixed 'make clean' to remove the fbhelp.o file.
 * Fixed the 'fbhelp' program to look for its files in /usr/local/fbhelp/
 * Fixed some tiny buffer overrun errors with muf debugging.
 * Fixed 'PID KILL' to kill the current program, without triggering a CATCH.
 * Fixed erroneous error messages in GUI_CTRL_COMMAND.
 * Fixed MCP GUI event handlers to return multi-line 'data' args.
 * Fixed irregular crasher bug with @shutdown.
 * Fixed various minor memory leaks.  Cleaned up freeing of non-leak allocations
 *   on shutdown, to make real memory leaks more apparent.
 * Fixed bad macro definition of gui_dlog_simple.
 * Fixed error with FORK muf prim not duplicating forstack and trystacks.
 * Fixed erroneous handling of proplists in simpleedit MCP package.
 * Fixed a bug where MCP packages weren't renegotiating on a program recompile.
 * Added GETPIDINFO ( i -- a ) muf primitive.  Returns a dictionary of info
 *   on the given specified process.  See muf helpfile for more usage info.
 * Added $pubdef muf preprocessor directive.  Sets a _defs/XXX prop on the prog.
 * Added $version muf directive.  Sets the _version prop on the program.
 * Added $lib-version muf directive.  Sets the _lib-version prop on the program.
 * Added $author muf directive.  Sets the _author prop on the program.
 * Added $note muf directive.  Sets the _note prop on the program.
 * Added $abort muf directive.  Aborts the compile, giving a message.
 * Added $cleardefs muf directive.  Resets macro definitions to default set.
 * Added $ifver, $ifnver, $iflibver, $ifnlibver muf directives.  Like $ifdef.
 * Added $iflib, $ifnlib, $ifcancall, $ifncancall muf directives.  Like $ifdef.
 * Added the ability to allow wizards to use the OVERIDE_TOKEN on WHO.
 * Added new @tune -- lazy_mpi_istype_perm.  This changes the permissions for
 *   {istype} to be the lazy, pre-5.56 method, allowing {istype} to reference
 *   remote objects.
 * Added docs of supported MCP GUI ctrl-commands to the GUI_CTRL_COMMAND muf
 *   manual entry.
 * Added "data" argument for MCP GUI events context.  This is the data for the
 *   event, if any, sent by the client.
 * Added PROGRAM_GETLINES ( d i1 i2 -- a ) muf primitive.  Returns a list array
 *   of strings containing the muf program lines in program d, from line i1 to
 *   line i2, inclusive.  If both i1 and i2 are zero, then the entire program
 *   is returned.  If i1 is zero, it is assumed to mean the first line.  If i2
 *   is zero, it is assumed to mean the very last line.  If i2 and i2 are the
 *   same, and non-zero, then only that line will be returned, as a list array
 *   with a single string element.  The target program must be controlled by
 *   the current program's UID, be set VIEWABLE, or the current program must
 *   be running with wizard permissions.
 * Added ARRAY_CUT ( a1 @ -- a2 a3 ) muf primitive.  Given an array, and an
 *   index into the array, cuts the array into two arrays at that position.
 *   The first array output will contain all array items before the given
 *   index.  The second array will contain the given position and all items
 *   after it.  When used on a list array, both output arrays will be list
 *   arrays.  When used on dictionaries, both arrays will be dictionaries.
 * Added ARRAY_COMPARE ( a1 a2 -- i ) muf primitive.  Compares two arrays
 *   using the same ordering assumptions as ARRAY_SORT in case sensitive
 *   ascending order mode.  If the two arrays are identical, this returns 0.
 *   If the first array is considered greater than the second, this returns
 *   a positive value.  If the second array is considered greater, this
 *   returns a negative value.  I'm not sure if the greater/lesser-than
 *   comparison results are really useful, though.
 * Added DIFF3 ( fx1 fy1 fz1 fx2 fy2 fz2 -- fx' fy' fz' ) muf primitive.
 *   Returns three floats, being the differences of fx1 - fx2, fy1 - fy2,
 *   and fz1 - fz2, respectively.
 * Added DESCRSECURE? (d -- i) muf primitive.  Returns 1 if the descriptor
 *   number corresponds to a secure connection, and 0 otherwise.
 * Added MCP_MUF_MLEV @tune option to specify the mucker level required to
 *   use MCP and MCP-GUI muf calls.
 * Added support for encrypted SSL connections.  See README.ssl
 * Added {eval!} MPI function that acts like {eval} except it doesn't unbless.
 * Changed MUF debug line display to show PID of process being debugged.
 * Changed {eval} to unbless the code it evaluates, for security reasons.
 * Changed {index}, {index!}, {rand}, and {timesub} to properly check the
 *   blessing of the property they evaluates.
 * Changed muf PMATCH primitive to accept "me", returning the player.
 * Changed @list to view only muf programs set VIEWABLE, as opposed to LINK_OK.
 * Changed commands_per_time input quotas to not count MCP messages.
 * Changes player name checks to prohibit ( and ) in player names.
 * Changed MCP GUI event callback arguments to include the McpMesg.
 * Changed password-change errors more informative, so "Sorry." isn't seen.
 * Changed default setting for GOD_PRIV to be defined, not undef'd.
 * Changed database format to Foxen6.  Programs in earlier databases that are
 *   set LINK_OK will also get their VIEWABLE flag set.
 * Changed 'resolver' spawning behavior to first try to spawn from the
 *   installation's bin/ directory, then from the standard locations.
 * Changed MCP code to flush long messages periodically to try to bypass
 *   '<Output Flushed>' events.
 *
 *
 *
 * 2.2fb6.00b3
 * Fixed a crasher bug with uninitialized watchpid-related variables.
 * Fixed ARRAY_FILTER_PROP muf primitive so it actually works.
 * Added NEXTENTRANCE ( d1 d2 -- d3 ) muf primitive.  Searches the database for
 *   the next object after d2 that is linked to d1.  You can begin a search by
 *   passing #-1 as d2.  The search currently scans upwards through the database,
 *   but this ordering is not guaranteed.  If an object is found that links to
 *   d1, then the dbref of that object is returned.  If no more such objects
 *   are found in the db, then #-1 is returned.
 * Added NEWPLAYER ( s1 s2 -- d ) muf primitive.  Creates a new player object,
 *   with the name s1, and the password s2.  This returns the dbref of the new
 *   player object.
 * Added COPYPLAYER ( d1 s1 s2 -- d2 ) muf primitive.  Creates a new player
 *   object with the name s1, and the password s2, and the properties, flags,
 *   links, etc. of the template object d1.  This returns the dbref of the
 *   newly created player object.
 * Added OBJMEM ( d -- i ) muf primitive.  Returns the current number of bytes
 *   in use by the given object.
 * Added INSTANCES ( d -- i ) muf primitive.  Returns the number of active
 *   instances of the given program.  Ie: the number of active processes that
 *   are running, using the given program.
 * Added COMPILED? ( d -- i ) muf primitive.  Returns 0 if the given program
 *   is not compiled.  Otherwise returns the number of compiled instructions.
 * Added NEWPROGRAM ( s -- d ) muf primitive.  Creates a new program object
 *   with the given name, and returns its dbref.
 * Added CONTENTS_ARRAY ( d -- a ) muf primitive.  Returns a list array that
 *   contains the dbref of every object contained within the given object.  If
 *   a #-1 is returned as the last list item, then there were too many objects
 *   to return all of them.
 * Added EXITS_ARRAY ( d -- a ) muf primitive.  Returns a list array that
 *   contains the dbref of every exit attached to the given object.  If a
 *   #-1 is returned as the last list item, then there were too many exits
 *   to return all of them.
 * Added GETLINKS_ARRAY ( d -- a ) muf primitive.  Returns a list array that
 *   contains the dbref of every object that the given object is linked to.
 * Added NEWPASSWORD ( d s -- ) muf primitive.  Changed the password of the
 *   given player d to s.
 * Added COMPILE ( d i1 -- i2 ) muf primitive.  Compiles the given program.
 *   If i1 is true, errors and warnings are printed out to the user.  If the
 *   program fails to compile, this returns 0.  If the compile is successful,
 *   this returns the number of compiled instructions.  This will throw an
 *   error if the program has any current instances running.
 * Added UNCOMPILE ( d -- ) muf primitive.  Uncompiles the given muf program.
 *   This will throw an error if the program has any current instances running.
 * Added GETPIDS ( d -- a ) muf primitive.  Returns a list array containing the
 *   pids of all the processes running the given program.  If #-1 is passed to
 *   this, then the array will contain the pids of all active processes.
 * Added TOADPLAYER ( d1 d2 -- ) muf primitive.  @toads player d2, and chowns
 *   all their posessions to player d1.  You can't toad wizard players.
 *
 *
 *
 * 2.2fb6.00b2
 * Fixed bug with MCP not properly dealing with \r's in arg strings.
 * Fixed bug where being set !C didn't strip ANSI color from muf NOTIFYs.
 * Fixed DoS security hole with exhausing memory via huge MCP messages.
 * Changed MCP GUI code to limit to 256 "values" per dialog.
 * Changed EVENT_SEND to send a dictionary instead of just a value.  The array
 *   will contain "data" with the value, "caller_pid" with the pid of the caller,
 *   and "caller_prog" with the dbref of the caller.
 * Changed VEHICLE flag for muf progs to mean VIEWABLE, to let you @list them.
 *   Programs set LINK_OK are _not_ @listable unless they are also set VIEWABLE.
 * Added inserver muf define for C_MENU.
 * Added support for "valname" option to MCP GUI control creation.
 * Added a __fuzzball__ inserver MUF $define, set to 1, to let programmers
 *   differentiate between Fuzzball and ProtoMuck servers.
 * Added ++ and -- muf primitives.  They will increment or decrement ints, floats
 *   and dbrefs, and if passed a variable, they will increment/decrement the
 *   int, float, or dbref contained within the variable, much like in C.  When
 *   passed a variable, nothing is returned on the stack.  When passed an int,
 *   float, or dbref, the incremented/decremented value is returned.
 * Added DESCRLEASTIDLE ( d -- i ) muf primitive.  Returns the least idle
 *   connection descriptor for the given player.
 * Added DESCRMOSTIDLE ( d -- i ) muf primitive.  Returns the most idle
 *   connection descriptor for the given player.
 * Added FIRSTDESCR ( d -- i ) muf primitive.  Returns the most recent connection
 *   descriptor for the given player.  If #-1 is given, then this returns the
 *   descriptor of the most recent connection to the MUCK.
 * Added LASTDESCR ( d -- i ) muf primitive.  Returns the oldest connection
 *   descriptor for the given player.  If #-1 is given, then this returns the
 *   descriptor of the oldest connection to the MUCK.
 * Added DESCRDBREF ( i -- d ) muf primitive.  Returns the dbref of the player
 *   that is connected to the given descriptor connection.
 * Added DESCRTIME ( i -- i ) muf primitive.  Returns the length of time in
 *   seconds, since the given descriptor connected.
 * Added DESCRIDLE ( i -- i ) muf primitive.  Returns the length of time in
 *   seconds, that the given descriptor has been idle.
 * Added DESCRHOST ( i -- s ) muf primitive.  Returns the hostname that the
 *   given descriptor connection is connected from.
 * Added DESCRUSER ( i -- s ) muf primitive.  Returns the best guess at the
 *   username on the remote machine, that is connected to this descriptor
 *   connection.
 * Added DESCRBOOT ( i -- ) muf primitive.  Disconnects the given descriptor
 *   connection.
 * Added DESCRNOTIFY ( i s -- ) muf primitive.  Sends the given string message
 *   to the given descriptor connection.
 * Added PNAME-OK? ( s -- i ) muf primitive.  Returns true if the given string
 *   could be a valid playername.  Note that this does NOT check if the name
 *   is already in use or not.  Use pmatch for that.
 * Added NAME-OK? ( s -- i ) muf primitive.  Returns true if the given string
 *   could be a valid object name.
 * Added FORCE_LEVEL ( -- i ) muf primitive.  Returns the current force_level.
 *   This will tell you if the current program was run as a result of an @force.
 * Added 'fbhelp' compile target, to allow unix users to get FB help, man, and
 *   mpi documentation from the command line, without having to log in.  This
 *   only works if you did a 'make install', which copies the helpfiles to a
 *   useful place in the filesystem.  (/usr/local/fbmuck/help/*)
 * Added SORTTYPE_SHUFFLE inserver muf define for use with ARRAY_SORT, to
 *   randomize a list.
 * Added ->[] inserver muf define as a shortcut for array_setitem.
 * Added WATCHPID ( i -- ) muf primitive.  Sends a "PROC.EXIT.pid" event to
 *   the current process when the process referred to by the given pid exits.
 *   If the process process does not exist, the event will be sent immediately.
 *   The exit event can be retrieved by a call to EVENT_WAITFOR.  The event
 *   type will be "PROC.EXIT." with the pid of the process appended to it.
 *   The pid will also be returned as the data value from the event.  This
 *   primitive requires at least Mucker Level 3.
 * Added BLESSED? (d s -- i) muf prim.  Given an object and a property string,
 *   returns a boolean telling if that property is blessed.
 * Added four new data entries to USER muf event contexts sent by SEND_EVENT.
 *   "descr" contains the descriptor that initiated the sending program.
 *   "trigger" contains the dbref of the trigger that ran the sending program.
 *   "player" contains the dbref of the player that ran the sending program.
 *   "prog_uid" contains the dbref of the player used for permissions in the
 *   sending program.
 *
 *
 *
 * 2.2fb6.00b1
 * Fixed STOD to allow for trailing spaces after a number argument.
 * Fixed a bunch of minor FreeBSD compatability issues.
 * Fixed a permissions error in muf's SET primitive, with setting vehicle's bits.
 * Fixed crasher bug with the MUF code ': main repeat ;'
 * Fixed possible security hole in {testlock} with @props.
 * Fixed crasher bug in {listprops} with too many properties.
 * Fixed a bug with DESCR_ARRAY returning an array with bad entries.
 * Fixed a crasher bug with dequeuing muf programs with TIMERs.
 * Fixed a crasher bug in {lmember} when not specifying delimiter.
 * Fixed a buffer overwrite error in {parse} when given output delimiters.
 * Fixed a crasher bug in ARRAY_NUNION, ARRAY_NDIFF, and ARRAY_NINTERSECT.
 * Fixed a security hole in {lexec}.  All props in list must be blessed for
 *   blessed permissions to be in effect.
 * Added @bless and @unbless commands for granting wizbit mpi permissions to
 *   individual properties.  Syntax is @[un]bless object=propname.
 * Added MPI {bless:propname[,object]} command to bless a property.  Requires
 *   blessed permissions to bless a property.
 * Added MPI {unbless:propname[,object]} command to unbless a property.  Requires
 *   blessed permissions to unbless a property.
 * Added MPI {revoke:commands} command to run the given mpi commands without
 *   any Blessing that the running script may currently have.  This is good
 *   to wrap around {eval} statments to prevent security holes.
 * Added BLESSPROP (dbrefObject strPropname -- ) MUF primitive.  Blesses the given
 *   property for MPI.  Requires Wizbit perms.
 * Added UNBLESSPROP (dbrefObject strPropname -- ) MUF primitive.  Unblesses the
 *   given property for MPI.  Requires Wizbit perms.
 * Added GUI_CTRL_COMMAND (strDlogID strCtrlID strCommand dictArgs -- ) muf prim.
 *   This is the generic primitive for executing a GUI control specific command.
 *   The dictionary contains the arguments for the given command.
 * Added GUI_VALUE_GET (strDlogID strCtrlID -- arrValue) muf primitive.  This
 *   gets the current value of the given GUI control, and returns it as a string
 *   list array.
 * Added ARRAY_MATCHVAL (arrStrings strPattern - arrStrings) muf primitive.
 *   Given an array and an smatch pattern string, returns a dictionary containing
 *   all the key-value pairs where the value was a string that matched the given
 *   smatch pattern.
 * Added ARRAY_MATCHKEY (arrStrings strPattern - arrStrings) muf primitive.
 *   Given an array and an smatch pattern string, returns a dictionary containing
 *   all the key-value pairs where the key was a string that matched the given
 *   smatch pattern.
 * Added ARRAY_EXTRACT (array arrIndexes -- array') muf primitive.  Takes an
 *   array, and returns a dictionary containing every element of the original
 *   array who's key was in the list indexes given.
 * Added ARRAY_JOIN ([s] s -- s) muf primitive.  Takes a list array and a
 *   delimiter string, and returns a single string that is the concatenation
 *   of all the items in the list array, with the delimiter string in between.
 *   For example:   { "one" 2 "three" 3.14159 }list "... " array_join
 *   will result in a single string: "one... 2... three... 3.14159"
 * Added ARRAY_FILTER_PROP ([d] s1 s2 -- [d']) muf primitive.  Takes a
 *   homogenous list array of dbrefs, and returns a list array with only
 *   those dbrefs who have a property specified by s1, set to a value that
 *   smatch matches s2.
 * Added ARRAY_SORT (arrData intSortType -- arrSortedData) muf primitive.  This
 *   sorts all the items in the list array given, based on the given sort type.
 *   This can sort strings, integers, floats, dbrefs, or mixes of types.  Integers
 *   are sorted in with floats, but strings sort after all numbers.  Dbrefs sort
 *   after the other number types, but before string types.  Other stack item
 *   types will sort separately, but in an undefined consistent order.  The valid
 *   sort types are 0 - 3, which have the following inserver muf macro $defines:
 *     SORTTYPE_CASE_ASCEND     Case sensitive and ascending order.
 *     SORTTYPE_NOCASE_ASCEND   Case insensitive and ascending order.
 *     SORTTYPE_CASE_DESCEND    Case sensitive and descending order.
 *     SORTTYPE_NOCASE_DESCEND  Case insensitive and descending order.
 * Added TRY-CATCH-ENDCATCH exception handling.
 *   TRY ( i -- ) locks all but the top i stack items, so that any attempt to pop
 *     or change them will throw an error.  Any errors thrown inside a TRY-CATCH
 *     block will jump execution immediately to the CATCH.
 *   CATCH ( -- s ) denotes the start of exception handling code.  If an error is
 *     thrown in the TRY-CATCH block, then execution will jump immediately to this
 *     primitive.  If no error was thrown in the TRY-CATCH block, then the code in
 *     the CATCH-ENDCATCH block will not be executed.  This primitive will pop off
 *     all stack items not locked by the TRY, and then unlocks the stack.  The
 *     string error message that was thrown will be pushed onto the stack.
 *   ENDCATCH ( -- ) denotes the end of the CATCH block.
 *   The ABORT ( s -- ) primitive can be used to throw arbitrary errors.
 *   An example of using the TRY-CATCH-ENDCATCH structure is:
 *     : get_a_prop ( d s -- s )
 *         2 TRY
 *             getpropstr
 *         catch
 *             pop (We got an error trying to read the prop.  Ignore it.)
 *             ""
 *         endcatch
 *     ;
 * Added FINDNEXT ( d1 d2 s1 s2 -- d' ) muf primitive.  Searches for the next
 *   object in the database _after_ d1 that is owned by d2, whose name matches
 *   the wildcard pattern s1, and whose flags match those specified by s2.
 *   You can start a search with d1 set to #-1.  If d2 is #-1 then ownership
 *   checks will not be performed.  If s1 is an empty string, name checks will
 *   not be performed.  If s2 is a null string, flags will not be checked.
 *   s2 is a flagslist that is in the same format as that used by the @find,
 *   @owned, etc. commands.  ie:  "F3!D" will match all muf program objects in
 *   the database that are mucker level 3, and not set debug.  If there are
 *   no more objects in the database that might match all the search criteria,
 *   then #-1 is returned.  Otherwise, the next matching object is returned.
 *   This is used similarly to the NEXT primitive.  Ex:
 *     #-1 begin
 *         me @ "*.muf" "F" FINDNEXT
 *         dup while
 *         dup unparseobj .tell
 *     repeat
 * Added REFLIST_ADD ( d1 s1 d2 -- ) muf primitive.  Adds dbref d2 to the reflist
 *   in property s1 on object d1.  If d2 is already in the list, it is moved to
 *   the end of the reflist.
 * Added REFLIST_DEL ( d1 s1 d2 -- ) muf primitive.  Removes dbref d2 from the
 *   reflist in property s1 on object d1.  If d2 is not in the list, nothing
 *   happens.
 * Added REFLIST_FIND ( d1 s1 d2 -- i ) muf primitive.  Finds dbref d2 in the
 *   reflist in property s1 on object d1.  If d2 is not in the list, then 0 is
 *   returned.  Otherwise the position of the dbref in the list is returned,
 *   with the first dbref being in position 1, the second dbref in 2, etc.
 * Added support for multiple listener sockets, a la FB5.
 * Changed MPI to not use the trigger's wizbit for permissions.  Instead, if the
 *   property is itself Blessed, then it gets the permissions that wizbit mpi
 *   used to have.
 * Changed 'examine' command to list properties with either a '-' or a 'B' in
 *   front, to denote whether the property has been Blessed or not.
 * Changed the 'log_reads' @tune to 'log_interactive' to be compatible with fb5.
 * Changed EVENT_EXISTS to allow matching by smatch wildcard pattern.
 * Changes @bless and @unbless to (un)bless all props that match the given
 *   wildcard property name.
 *
 *
 *
 * 2.2fb6.00a33
 * Fixed 'make package' script to correct location of configure script.
 * Fixed a crasher bug with closing a the input db file before we are done with
 *   it, when DISKBASE is #undefed and DELTADUMPS is #defined.
 * Fixed a crasher bug where ARRAY_APPENDITEM checked the wrong argument's type.
 * Fixed a crasher bug with DESCR_SETUSER for players with null passwords.
 * Fixed a crasher bug with CHECKPASSWORD for players with null passwords.
 * Fixed a string termination bug in ARRAY_PUT_REFLIST.
 * Fixed a bug with ARRAY_GET_REFLIST not decompressing before parsing strings.
 * Fixed a bug with zombies not echoing text.  Bug was introduced in O(1) code.
 * Fixed a misleading error message with muf compiling 'begin if repeat'.
 * Fixed a bug with STRNCMP giving bad results with null string arguments.
 * Fixed a bug with PARSEPROP not being re-entrant.
 * Fixed a bug with STOD parsing #-3 as #-1.
 * Added MUD_GID support, to change group affiliation (like MUD_ID).
 * Added {timing} MPI command to show how long a command takes to execute.
 * Added @tops, @mpitops, and @muftops commands for showing processor hogs.
 * Added CMD_LOG_THRESHOLD_MSEC @tune option.  When a command takes longer than
 *   this many milliseconds to execute, it will be logged to the logs/cmd-times
 *   log file.
 * Added EVENT_WAITFOR (listEventIDs -- context strEventID) MUF prim.  This will
 *   wait for an event to occur that matches one of the eventid strings in the
 *   given string list array.  The first event in the event queue that matches
 *   will be removed from the event queue, and will be returned, with the
 *   apropriate context data.  If there is no matching event, then this process
 *   will pause until a matching event becomes available.  The eventIDs are
 *   case sensitive.
 * Added EVENT_EXISTS (strEventID -- intCount) MUF prim.  Returns the number
 *   of pending events that have the given eventID type.
 * Added sending of "READ" MUF events to foreground/preempt processes to let
 *   them know there is text to be READ from the user.  Only one process will
 *   get a "READ" event, in the extremely unusual case that there are two
 *   foreground/preempt processes at once.  The context for the "READ" event
 *   is the descriptor that the text was sent from.  Note that there will only
 *   be one READ event in the queue, even if the user sends multiple lines.
 *   The descriptor reported by this event will be the one that sent the first
 *   line.
 * Changed the build scripts to do 'configure' from the directory above src.
 * Changed the restart script to look for netmuck in /usr/local/fbmuck/bin/
 * Changed 'make install' to install the binaries to /usr/local/fbmuck/bin/
 * Changed 'get' command to disable zombie thieving of player/container contents.
 * Changed {ontime} and {idle} to refer to the least idle of a users connections.
 * Changed maximum MUF stacksize to 1024 elements.
 * Changed @ps to show the %CPU usage of MUF processes.
 * Changed examine to show cumulative runtimes for MUF programs.
 * Changed MPI parser to use more minimal amounts of heap space instead of huge
 *   amounts of stack space.  This may lead to smaller process sizes.  This will
 *   also unfortunately slow down MPI slightly.  The 26 recursion level limit
 *   may be raised significantly, though.
 * Changed EVENT_WAIT into an inserver macro that resolves to the commands
 *   "0 array_make event_waitfor"
 * Changed TREAD into an inserver macro that that uses MUF event timers and
 *   EVENT_WAITFOR to do the same thing.
 * Optimized {select} MPI command to make it fast on very sparse lists.
 * Optimized almost all MUF connection primitives to be O(1) instead of O(n),
 *   by using lookup tables instead of searching a linked list.
 *
 *
 *
 * 2.2fb6.00a32
 * Fixed more minor 64-bit compatability bugs with regards to time() calls.
 * Fixed problem with loading an older db leaving users in insert mode.
 * Fixed bug with ARRAY_GETRANGE returning a non-empty array when given a range
 *  that starts one beyond the end of the list array's content.
 * Fixed bug with ARRAY_VALS CLEAR()ing garbage when passed an empty array.
 * Fixed bug with @toad sending the inventory of the toader (not toadee) home.
 * Fixed several uninitialized variable problems.
 * Fixed a few bugs with functions being called with the wrong number of args.
 * Fixed a lot of compile-time warnings.
 * Added message to confirm exiting of insert mode in muf editor.
 * Added preliminary code to support READ mufevents.  This is incomplete.
 * Added EXPLODE_ARRAY (s s -- a) muf prim, as the array version of EXPLODE.
 * Changed the MUF compiler to use a single control_stack instead of separate
 *   if_stack and loop_stacks.
 *
 *
 *
 * 2.2fb6.00a31
 * Fixed an error message in MCP_REGISTER.  (required ML3, not wizbit.)
 * Fixed a bug with JMPs to function headers over-declaring scoped var sets.
 * Fixed a db corruption bug with @toading players.
 * Fixed bug #102350: if-else-then now won't interleave with begin-repeat.
 * Fixed multiple compile-time bugs with 64-bit systems.
 * Fixed ARRAY_GET_PROPLIST to return a list array instead of a dictionary.
 * Fixed bug where number() thought "+" and "-" were numbers.
 * Fixed POW to return 0.0 if the first arg is 0.
 * Fixed a crasher bug with {tell} and _listener programs on a room.
 * Changed the way MUF lvars work.  Called progs no longer get a copy of the
 *   caller prog's lvars.  However, if prog A calls into prog B which calls
 *   back into prog A, then both the inner and outer prog A have the same
 *   lvars, and changes made to one are seen by the other.  Prog B has its
 *   own lvars.  Basically, every different program dbref called will have
 *   its own lvars in that process.  The nice feature of this is that you
 *   can now make the equivalent of C-style static vars, which hold data
 *   persistently between calls into a lib.
 * Changed MCP_SEND to error out if the connection doesn't support the package.
 * Changed EVENT_SEND MUF prim to the following:
 *   EVENT_SEND ( i s ? -- ) Sends a "USER." event to the process referred
 *   to by the given pid.  The target process will receive an event that
 *   can be read with EVENT_WAIT.  The event type will be "USER." with the
 *   given event id string appended to it.  The given event id string will
 *   be truncated at 32 characters.  The event data argument will contain
 *   the sent data in the "data" element.  A "caller_pid" element will
 *   contain the process id of the caller, and a "caller_prog" element will
 *   have the dbref of the caller.  ie: '23 "foobar" 3.1416 event_send' will
 *   send an event to process 23, with an eventid of "USER.foobar", and a
 *   floating point data value of 3.1416 in the "data" element of the args
 *   dictionary that EVENT_WAIT will return.  This primitive requires at
 *   least Mucker Level 3.
 * Changed the rob command to give pennies to owner of robber puppets.
 * Changed MUF compiler to use an address linkage table, in preparation for
 *   possible alternate language support.
 * Optimized MUF interp to merge the FUNCTION/DECLVAR/INITVARS trio of instrs
 *   into a single FUNCTION instr.  This should improve speed slightly.
 * Optimized CLEAR and RCLEAR to use a switch statement.
 * Optimized copyinst() to use a switch statement.
 * Updated MUF manual (man.txt) to include docs for all muf primitives.
 * Added VAR! MUF compiler directive.  'var! foo' is the same as 'var foo foo !'.
 * Added internal primitives for one-inst SVAR get/set.
 * Added new MUF procedure declaration syntax, to allow the declaration and
 *   initialization of procedure-local variables from the stack.  Basically, if
 *   a procedure name ends with a '[' char, then that tells the compiler that
 *   you are specifying a list of variables that should be declared and init-
 *   ialized from the stack.  A ']' as a word terminates the list.  If a '--'
 *   is found before the ']', then anything from the '--' to the ']' gets
 *   ignored, and is treated sort of like a comment.  This lets coders specify
 *   what this procedure is expected to return.  Each variable can also be
 *   preceeded by an arbitrary type name and a colon (':'), as sort of a comment
 *   to show what stack item types it is expected to be.  The line:
 *       : myproc[ str:foo int:bar dbref:baz -- lock:qux ]
 *   gets effectively translated to:
 *       : myproc var! baz var! bar var! foo
 *   Note that the type name and return section are optional, so the line:
 *       : myproc[ foo bar baz ]
 *   is effectively the same as the above example.  The declaration of the
 *   returned values is _highly_ reccommended, though.  Type names may later
 *   get used to test that the passed arguments are of the right types, auto-
 *   matically.  This means that the type name should be one of 'addr', 'arr',
 *   'dbref', 'dict', 'float', 'int', 'lock', 'str', 'var', or 'lvar'.
 * Added MCP_REGISTER_EVENT ( strPkgName fltMinVers fltMaxVers -- ) MUF prim.
 *   Registers an MCP package so that clients can know what is supported, and
 *   marks this process as wanting to receive MCP messages as Muf Events.
 *   These events can be read with EVENT_WAIT, and will have event ids starting
 *   with "MCP.", followed by the package and message names.  The event data
 *   will be a dictionary, containing "descr", "package", "message", and "args"
 *   elements.  The args element will have a dictionary of message arguments as
 *   it's value.  The minimum and maximum package versions supported are
 *   represented as floating point numbers, with the minor version number being
 *   divided by 1000.  For example, an MCP package of version 1.1 is represented
 *   as 1.001, and a version of 1.23 is represented as 1.023.  This lets you use
 *   arithmetic compares to check version numbers.  Since this primitive arranges
 *   for MCP messages to be received as muf events, there is no need to use the
 *   MCP_BIND primitive with this.  A side benefit is that _any_ MCP message
 *   sent for this package can be caught, not just the ones you bound.  Also,
 *   the process that will handle the events is kept alive, so your data stored
 *   in variables, or on the stack, is kept.
 * Added ANSI_MIDSTR ( s i i -- s' ) MUF prim.
 *   Does exactly what MIDSTR does, except it ignores ansi escapes when
 *   determining what section of the string to extract.
 *
 *
 * 2.2fb6.00a30
 * Reformatted all code to a uniform code style based off of K&R.
 * Removed GUI_DLOG_SIMPLE MUF primitive and replaced it with a macro that
 *   uses the new GUI_DLOG_CREATE primitive.
 * Removed GUI_DLOG_TABBED MUF primitive and replaced it with a macro that
 *   uses the new GUI_DLOG_CREATE primitive.
 * Removed GUI_DLOG_HELPER MUF primitive and replaced it with a macro that
 *   uses the new GUI_DLOG_CREATE primitive.
 * Added MAX_VARIABLE_COUNT $define to let MUF programs know what the highest
 *   variable number can be for Vars, Local Vars, and Scoped Vars.
 * Added an EXPANDED_DEBUG_TRACE @tune option to allow display of expanded
 *   array contents in MUF debug trace output.
 * Added an PROCESS_TIMER_LIMIT @tune option to specify the maximum number
 *   of timers allowed to any one process.  This defaults to 4.  See the
 *   description of timers in TIMER_START.
 * Added PROPLIST_INT_COUNTER @tune, to specify whether the system standard
 *   for proplist storage is to use integer or string props for the counter.
 * Added PROPLIST_ENTRY_FMT @tune, to specify the system standard naming
 *   format for proplists.  ie: lists of data stored in properties like
 *   _list#:3    _list#/1:One    _list#/2:Two    _list#/3:Three
 *   This string specifies the format of the names of the properties that
 *   each list items is stored in.  Any instance of P in this string will
 *   be replaced by the proplist name.  Any instances of N in this string
 *   will be replaced by the item's number.  All other characters will be
 *   taken literally.  The default is: "P#/N" which will make for proplists
 *   which store their items in props like  _list#/1:First
 * Added an ARRAY_DIFF      convenience macro define for '2 array_ndiff'.
 * Added an ARRAY_UNION     convenience macro define for '2 array_nunion'.
 * Added an ARRAY_INTERSECT convenience macro define for '2 array_nintersect'.
 * Added an ERR_DIVZERO?    convenience macro define for '0 is_set?'
 * Added an ERR_NAN?        convenience macro define for '1 is_set?'
 * Added an ERR_IMAGINARY?  convenience macro define for '2 is_set?'
 * Added an ERR_FBOUNDS?    convenience macro define for '3 is_set?'
 * Added an ERR_IBOUNDS?    convenience macro define for '4 is_set?'
 * Added a D_SIMPLE inserver define for specifying "simple" dialogs.
 * Added a D_TABBED inserver define for specifying "tabbed" dialogs.
 * Added a D_HELPER inserver define for specifying "helper" dialogs.
 * Added EVENT_SEND ( i s ? -- ) MUF prim.  Sends a "USER." event to
 *   the process referred to by the given pid.  The target process will
 *   receive an event that can be read with EVENT_WAIT.  The event type
 *   will be "USER." with the given event id string appended to it.
 *   The given event id string will be truncated at 32 characters.  The
 *   given arbitrary stack element will be passed on to the new process.
 *   ie: '23 "foobar" 3.1416 event_send' will send an event to process
 *   23, with an eventid of "USER.foobar", and a floating point data
 *   value of 3.1416.  This primitive requires at least Mucker Level 3.
 * Added TIMER_START ( i s -- ) MUF prim.  Requests that a timer event
 *   be sent to this program in i seconds, with an event name of "TIMER."
 *   with the given string appended.  ie: '5 "one" timer_start' will
 *   cause a "TIMER.one" event to be sent to the program in 5 seconds.
 *   This is used with EVENT_WAIT.  If a timer with the given timerid
 *   already exists, it will be rescheduled to occur after the new delay.
 *   Timer ids will be truncated to 32 characters.  Each MUF process can
 *   only have a limited number of timers, specified by the @tunee setting
 *   'process_timer_limit'.  Timers are listed on the @ps timequeue with
 *   the PID of the timer's process in parentheses.  Timers are one-shot
 *   events.  To get a repeating timer, you'll need to restart it when
 *   you process a new timer event.
 * Added TIMER_STOP ( s -- ) MUF prim.  Stops the timer with the given
 *   timerid, if it exists.  If there is already a timer event on the
 *   event queue, it will STAY on the queue until processed.  As with
 *   the timer_start primitive, the "TIMER." part of the event name is
 *   assumed.  '"first" timer_stop' will stop the timer created by
 *   '5 "first" timer_start'.  Timer ids ARE case sensitive.
 * Added EVENT_COUNT ( -- i) MUF prim.  Returns the number of pending
 *   events waiting to be processed with EVENT_WAIT.
 * Added ANSI_STRLEN ( s -- i ) MUF prim.  Returns the length of string s
 *   ignoring ansi escape within the string.
 * Added ANSI_STRCUT ( s i -- s1 s2 ) MUF prim.  Like STRCUT, but ignores ansi
 *   escapes when finding the location to divide the string at.
 * Added ANSI_STRIP ( s -- s' ) MUF prim.  Takes a string and removes ansi
 *   escapes from with in the string, returning the de-ansified string.
 * Added GUI_DLOG_CREATE (intDescr strType strTitle dictArgs -- strDlogID)
 *   If a user has a client that can support the MCP GUI protocol, then this
 *   primitive can be used to generate a dialog on their screen.  The intDescr
 *   is the integer descriptor of the connection to show the dialog on. The
 *   strType is the type of the dialog to create.  Currently, the only options
 *   for strType are D_SIMPLE, D_TABBED, or D_HELPER.  The strTitle argument is
 *   the title to show in the titlebar of the dialog.  dictArgs is a dictionary
 *   array that contains extra optional arguments for creating the dialog.
 *   In general, dictArgs is only used to specify "panes" and "names" for
 *   D_TABBED and D_HELPER dialogs.  This primitive returns a string containing
 *   the dialogid, used by other prims to add controls or make various changes.
 *   This dialog will be hidden and not shown to the user until it has been
 *   displayed with the GUI_DLOG_SHOW command.
 * Added ARRAY_APPENDITEM ( ? a -- a') MUF prim.  Appends the given item to
 *   the given list array.
 * Added SETSYSPARM ( s1 s2 -- ) MUF prim.  Assigns the @tunable parameter s1
 *   a value given by s2.  s2 must contain a legal value for s1. (wizbit only)
 * Added ARRAY_FINDVAL (a1 ? -- a2) MUF prim.  Returns a list array containing
 *   the keys of every element in the array a1 whose values match the given
 *   value.
 * Added ARRAY_EXCLUDEVAL (a1 ? -- a2) MUF prim.  Returns a list array containing
 *   the keys of every element in the array a1 whose values did NOT match the
 *   given value.
 * Added ARRAY_GET_PROPDIRS( d s -- a ) MUF prim.  Returns a list array
 *   containing the names of all the sub-propdirs contained within the given
 *   propdir.  Any propdirs the program wouldn't be able to read, are left out.
 *   (ML3 required.)
 * Added ARRAY_GET_PROPVALS ( d s -- a ) MUF prim.  Reads in properties from
 *   a propdir, and returns them in a dictionary, keyed by propname.  Sub-
 *   propdirs in the given propdir that do not have any value of their own,
 *   are left out of the returned dictionary.  Properties that the program
 *   doesn't have perms to read are also left out.  Reads up to 511 props
 *   maximum. (ML3 required.)
 * Added ARRAY_PUT_PROPVALS ( d s a -- ) MUF prim.  Takes the values in
 *   the given dictionary, and stores them in the given propdir on the
 *   given object.  Each dictionary entry will be saved into a property
 *   with the key as the name, and the value as the property value.
 *   Be aware that dictionary entries with keys starting with one of
 *   @ ~ _ or . may require special permissions to save.
 * Added ARRAY_PUT_REFLIST ( d s a -- ) MUF prim.  Takes a list array of
 *   dbrefs, and stores them in a property as a space delimited string of
 *   dbrefs.  ie:  "#1234 #6646 #1026 #7104"
 * Added ARRAY_GET_REFLIST ( d s -- a ) MUF prim.  Reads in list of space
 *   delimited dbrefs from a string property, and returns them as a list
 *   array of dbrefs.  See ARRAY_PUT_REFLIST for property syntax.
 * Added ARRAY_GET_PROPLIST ( d s -- a ) MUF prim.  Reads in properties from
 *   a classic style proplist, and returns them in a dictionary, keyed by
 *   propname.  Proplists can be in any of the common proplist styles:
 *   ie: "propname#/1", "propname/1", or "propname1".  If the program
 *   doesn't have permission to read the list, it returns an empty
 *   dictionary.  Reads up to 511 props maximum.
 * Added ARRAY_PUT_PROPLIST ( d s a -- ) MUF prim.  Takes the values
 *   in the given list array, and stores them in the given propdir on
 *   the given object as a sequential proplist.  This will use the
 *   system standard proplist format specified by @tune settings.
 * Added PROPLIST_COUNTER_FMT @tune, to specify the system standard naming
 *   format for proplists.  ie: lists of data stored in properties like
 *   _list#:3    _list#/1:One    _list#/2:Two    _list#/3:Three
 *   This string specifies the format of the name of the property that
 *   the count of list items is stored in.  Any instance of P in this
 *   string will be replaced by the proplist name.  All other characters
 *   will be taken literally.  The default is: "P#" which will make for
 *   proplists which store their count in props like  _list#:3
 * Added ARRAY_REVERSE (a -- a') MUF prim many versions ago, but forgot to
 *   note it here before.  Takes a list array and reverses its order.
 * Fixed crasher bug with MCP-GUI and players logging out and back in.
 * Fixed a nasty bug where ARRAY_GETITEM was retrieving CLEARed values.
 * Fixed a minor bug in fmtstring to handle arrays for %? formats.
 * Fixed a crasher bug with using various MPI commands on #0.
 * Fixed a bug to make XYZ_TO_POLAR and POLAR_TO_XYZ set the NAN flag and
 *   return 0.0's, like the rest of the FP prims do.
 * Fixed a crasher bug in MCP when client fails to send authentication key.
 * Fixed bug with stringpfx and null string arguments.
 * Changed ARRAY_GETRANGE to return empty list for out of range indexes.
 * Changed the MIDSTR muf prim to consider the first char of a string to be
 *   position 1, instead of 0.  This makes it match the results of instr.
 *
 *
 *
 * 2.2fb6.00a29
 * Added boolean secure_thing_movement @tune param.  Enables triggering of the
 *   _arrive/, _depart/, etc. propqueues for Thing objects as well as Players.
 *   This can cause server processing overhead, but it allows more certain
 *   tracking of object movement via MUF/MPI.
 *
 *
 *
 * 2.2fb6.00a28
 * Fixed a possible crasher bug with blank MUF program lines.
 * Fixed @mcpedit so it will display compile errors.
 * Fixed bug where MCP wouldn't split up multiline MUF strings with \r chars.
 * Fixed a crashing bug in the MUF INTERP primitive.
 * Fixed a crashing bug with @ps listing of MPI processes for non-wizards.
 * Fixed a reference count bug in array_getitem muf primitive.
 * Fixed a different reference count bug in many array_* prims.
 * Changed Boolexp parsing code to make it re-entrant.
 * Changed muf instruction display code to make it re-entrant.
 * Removed buggy propdir_diskbasing code completely.
 * Added \r\n's to the ends of the shutdown messages.
 * Added the ability to print the contents of scoped vars in the muf debugger.
 * Added the WIZCALL MUF keyword.  Used like the PUBLIC keyword, but the calling
 *   program requires wizbit permissions to call the function.
 * Added the following MUF primitives:
 *     CANCALL?  (d s -- i)
 *         Will return true if the given program has a public or wizcall function
 *         that the current program has permissions to call.  Returns false,
 *         otherwise.
 *     ONLINE_ARRAY  ( -- a)
 *         This is the same as the ONLINE primitive, except it returns a single
 *         stack item which is an array of dbrefs instead of pushing every dbref
 *         separately onto the stack.
 *     DESCR_ARRAY  (d -- a)
 *         This returns an array of descriptors that are associated with the
 *         given dbref.  This is effectively the same as the sequence
 *         'descriptors array_make'.
 *     {  ( -- mark)
 *         Pushes a marker onto the stack, for use with the }, }LIST, and }DICT
 *         commands.
 *     }  ( mark ?n ... ?1 -- ?n ... ?1 i )
 *         Returns the count of how many stack items exist between the topmost
 *         stack marker and the top of the stack.  That stack marker is removed
 *         from the stack, and the count is pushed onto the top of the stack.
 *         This is useful for automatically counting a number of static strings,
 *         and other such things.
 *     }LIST  ( mark ?n ... ?i -- array )
 *         MUF primitive.  This takes all the stack items above the topmost stack
 *         marker, and makes a list from them, a la array_make.  In fact, this is
 *         implemented as an inserver macro with a definition of '} array_make'.
 *     }DICT  ( mark @n ?n ... @1 ?1 -- dict )
 *         This takes all the pairs of names (@s) and values (?s) between the
 *         top of the stack and the topmost stack marker, and makes them into
 *         a dictionary, a la the array_make_dict primitive.  In fact, this is
 *         implemented as an inserver macro with a definition of
 *         '} 2 / array_make_dict'.
 *     DESCR  ( -- i)
 *         Returns the connection descriptor that invoked the currently running
 *         program.  This may return -1 for some listener or autostart programs.
 *     TOKENSPLIT  (strString strDelim strEscape -- strPre strPost strChar)
 *         Searches strString for the first character that matches any character
 *         in strDelim, so long as it is not escaped by the character passed in
 *         strEscape.  Returns the unescaped string before the found character,
 *         the raw string after that character, and the character that was found.
 *     GUI_AVAILABLE  (intDescr -- fltVersion)
 *         Returns the floating point version number of the MCP GUI protocol
 *         supported by the given descriptor's connection.  The version is
 *         encoded in the number such that major version 8, minor version 12
 *         is represented as 8.012.  If the MCP protocol is not available on
 *         that descriptor, then 0.0 is returned.
 *     GUI_DLOG_SIMPLE  (intDescr strTitle -- strDlogID)
 *         If a user has a client that can support the MCP GUI protocol, then
 *         this primitive can be used to generate a simple dialog on their
 *         screen.  By "simple" I mean just an empty window with no controls.
 *         The intDescr argument specifies what connection descriptor to
 *         create the dialog for (ie: what user's screen to show it on), and
 *         the strTitle arg specifies what the title of the dialog will be.
 *         This returns a string containing the dialogid, used by other prims
 *         to add controls or make various changes.  This dialog will be hidden
 *         and not shown to the user until it has been displayed with the
 *         GUI_DLOG_SHOW command.
 *     GUI_DLOG_TABBED  (intDescr strTitle dictPages -- strDlogID)
 *         If a user has a client that can support the MCP GUI protocol, then
 *         this primitive can be used to generate a tabbed dialog on their
 *         screen.  By "tabbed" I mean a window with a tabbed notebook, similar
 *         to Win95 "property sheets", with three standard buttons at the bottom.
 *         The standard buttons return values of "_ok", "_cancel", and "_apply".
 *         The intDescr argument specifies what connection descriptor to create
 *         the dialog for (ie: what user's screen to show it on).  The strTitle
 *         arg specifies what the title of the dialog will be.  The dictPages
 *         argument is a dictionary array of page ids and display names to be
 *         created.  (ids as dictionary keys, display names as vals) This prim
 *         returns a string containing the dialogid, used by other prims to add
 *         controls or make various changes.  When you create a new control, you
 *         can specify which page to put it in by passing a pageid in as the
 *         value of the "pane" argument.  This dialog will be hidden and not
 *         shown to the user until it has been displayed with the GUI_DLOG_SHOW
 *         command.
 *     GUI_DLOG_HELPER  (intDescr strTitle dictPages -- strDlogID)
 *         If a user has a client that can support the MCP GUI protocol, then
 *         this primitive can be used to generate a helper dialog on their
 *         screen.  By "helper" I mean a dialog similar to a Win95 wizard dialog.
 *         The standard buttons return values of "_cancel", and "_finish".
 *         The intDescr argument specifies what connection descriptor to
 *         create the dialog for (ie: what user's screen to show it on), and
 *         the strTitle arg specifies what the title of the dialog will be.
 *         The dictPages argument is a dictionary array of page ids and display
 *         names to be created.  (ids as dictionary keys, display names as vals)
 *         This returns a string containing the dialogid, used by other prims
 *         to add controls or make various changes.  When you create a new
 *         control, you can specify which page to put it in by passing a pageid
 *         in as the value of the "pane" argument.  This dialog will be hidden
 *         and not shown to the user until it has been displayed with the
 *         GUI_DLOG_SHOW command.
 *     GUI_DLOG_SHOW  (strDlogID -- )
 *         Forces a given dialog to be shown to the user.  The strDlogId is what
 *         was returned by the GUI_DLOG_CREATE (or similar) command.
 *     GUI_DLOG_CLOSE  (strDlogID -- )
 *         Forces a given dialog to be closed and destroyed.  The strDlogId is
 *         what was returned by the GUI_DLOG_CREATE (or similar) command.
 *     GUI_CTRL_CREATE  (strDlogID strType strCtrlID dictArgs -- )
 *         Creates a new control in a given dialog.  strDlogID contains the
 *         dlogid returned from a GUI_DLOG_SIMPLE (or similar) command.  strType
 *         contains the control type.  To make debugging easier and faster,
 *         MUF $defs have been provided for each control type.  They are:
 *         C_DATUM, C_LABEL, C_HRULE, C_VRULE, C_BUTTON, C_CHECKBOX, C_EDIT,
 *         C_MULTIEDIT, C_COMBOBOX, C_SPINNER, C_SCALE, C_LISTBOX, C_FRAME,
 *         and C_NOTEBOOK.  If you use these instead of the actual type name
 *         strings, then if you mistype one, it will throw an error when trying
 *         to compile, instead of when you try to run it.  The strCtrlID arg
 *         is the id to give the control, for use in reading the values back
 *         later, or modifying the control.  dictArgs is used to pass any other
 *         arguments needed to create the control.  This will be used by almost
 *         all controls.  It is a dictionary array that contains argnames as
 *         keys, each with an argument value.
 *     GUI_VALUES_GET   (strDlogID -- dictValues)
 *         Returns a dictionary containing all the control values for the given
 *         dialog.  The keys are the control ids.
 *     GUI_VALUE_SET    (strDlogID strCtrlID strValue -- )
 *         Sets the value of a given control in a given dialog.
 *     EVENT_WAIT       ( -- dictContext eventID)
 *         Waits for an event to occur, pausing the MUF program.  Currently, the
 *         only events are GUI events.  GUI events have eventID strings that are
 *         created by prepending "GUI." to the dlogID of the dialog that generated
 *         the event.
 *     []    (a @ -- ?)
 *         Defined to be the same as array_getitem
 *     [..]    (a @1 @2 -- a')
 *         Defined to be the same as array_getrange
 *
 *
 *
 * 2.2fb6.00a27
 * Fixed a bug in the MALLOC_PROFILING code.  (Thanks, Cynbe!)
 * Fixed a few compiler warnings about main() not returning int.
 * Fixed a bug in the ITOC muf primitive that returned random words for
 *   values greater than 127.
 * Added the ATAN2 (fy fx -- f) MUF primitive.  Equivalent to atan(fy/fx),
 *   but takes the signs of the arguments into account, and avoids DIVBY0.
 * Added the DIST3D (fx fy fz -- f) MUF primitive.  Returns the distance of
 *   XYZ coords (fx, fy, fz) from the origin.
 * Added the XYZ_TO_POLAR (fx fy fz -- fr ft fp) MUF primitive.  This converts
 *   the XYZ coordinate (fx, fy, fz) to the spherical polar coord (fr, ft, fp).
 * Added the POLAR_TO_XYZ (fr ft fp -- fx fy fz) MUF primitive.  This converts
 *   the spherical polar coordinate (fr, ft, fp) to the XYZ coord (fx, fy, fz).
 * Added MOVEPENNIES (d1 d2 i -- ) moves i pennies from player/thing d1 to play-
 *   er/thing d2.  I think the perms on this will need to be rewritten as soon
 *   as we figure out what they SHOULD be.  This is the first step towards mak-
 *   ing ADDPENNIES require at least ML3 (or wizbit), for enabling economies.
 *   Thanks to David McClure for this mod.
 * Added @tune autolook_cmd to allow changing what action to run when entering
 *   a room.  This defaults to "look".  This was a feature request.  Thanks to
 *   Loki for this mod.
 *
 *
 *
 * 2.2fb6.00a26
 * Fixed a crasher bug with multi-line MCP messages.
 * Fixed several parsing bugs with the dns-org-mud-moo-simpleedit MCP package.
 *
 *
 *
 * 2.2fb6.00a25
 * Fixed a crasher bug in MCP introduced in a previous bugfix.
 *
 *
 *
 * 2.2fb6.00a24
 * Fixed several related crasher bugs, triggered by failure to run MUF progs.
 *
 *
 *
 * 2.2fb6.00a23
 * Fixed a crasher bug caused by a wild pointer in the MCP negotiation code.
 *
 *
 *
 * 2.2fb6.00a22
 * Log Read/Interactive ability added.  By setting the boolean @tune option
 *  'log_reads' to 'yes' (default 'no'), any commands entered while in the
 *  interactive or read mode (due to server action or MUF 'read' prim) will
 *  be sent to the server command log with appropriate annotation.  Be
 *  warned that this could cause quite a bit of spammage in your log file,
 *  and certainly will replicate (though not in nice order), some information
 *  that is included under program logging.
 * Enable/Disable 'Home'.  By setting the boolean @tune option 'enable_home'
 *  to 'no' (default 'yes'), the global in-server 'home' command will cease
 *  to work.  This allows the MUCK administrator to create a programmatic
 *  or other customized 'home' action, or to have none at all for MUCKs where
 *  the 'home' command would not be in-theme.
 * Xpress or prefix commands.  By setting the @tune option 'enable_prefix'
 *  to 'yes' (default 'no'), the server gains the ability to do internal
 *  matches against actions much in the way the in-server '"' and ':' work.
 *  To set up a prefix command, create an action linked to a program as you
 *  normally would.  Make sure the action is owned by a wizard.  Then have
 *  the wizard set the 'X' flag on the command and make sure the @tune
 *  option is set.  At this point, any of the 'names' set on the action
 *  are now 'prefix' names and will be matched against the beginning of
 *  the user's command string.  For example, a prefix action called '&;foo'
 *  will match both '&yadda' and 'fooBar'.
 * Bug fix for prim_online.  A rare crashing bug was found in the MUF
 *  'online' primitive, where when the exact number of people online were
 *  exactly two more than the remaining MUF stack size, the stack top
 *  limit would be exceeded, causing a SEGV further down MUF execution.
 *
 *
 *
 * 2.2fb6.00a21
 * Fixed usage of first_prop() and first_prop_nofetch() to be 64bit clean.
 * Fixed a string termination bug in @open.
 * Fixed a crasher bug with reading float props stored as 1 instead of 1.0.
 * Fixed a compile-time bug with #undefing DISKBASE.
 * Fixed a crasher bug with the {parse} mpi primitive.
 * Changed the search restrictions for MPI _msgmacs/ macros.  Now when MPI
 *   looks for a macro, it uses the following algorithm:
 *       Check the owner of the trigger.
 *       Check the Trigger itself.
 *       Check each object down the environment from the trigger that is
 *     owned by the same player as the trigger.
 *       Check #0.
 * Changed mpi {store} permissions, to refuse to store props to properties
 *   under _msgmacs/ unless the mpi has wizardly permissions.
 * Changed muf to require at least mucker level 3 to store any properties
 *   in or under _msgmacs/ propdirs.
 * Changed the muf compiler to be thread-safe. (Planning for future.)
 * Removed Balloc for not being very useful, and not being 64bit clean.
 * Added low-level MCP (Mud-Client Protocol) support.  This is a protocol
 *   used to allow the server to communicate data to client programs.
 * Added the following MCP primitives to support MCP:
 *   MCP_REGISTER ( strPkgName fltMinVers fltMaxVers -- )
 *       Registers an MCP package so that clients can know what is supported.
 *       The minimum and maximum versions supported are represented as floating
 *       point numbers, with the minor version number being divided by 1000.
 *       For example, an MCP package of version 1.1 is represented as 1.001,
 *       and a version of 1.23 is represented as 1.023.  This lets you use
 *       mathematical compares to check version numbers.
 *   MCP_BIND ( strPkgName strMesgName addrCallback -- )
 *       Binds a specific message, so if it is received, the given function is
 *       called.  The callback function is assumed to accept the args:
 *       ( intDescr dictArgs -- ) where dictArgs is a dictionary array contain-
 *       ing key-value pairs that represent the arguments of the message.  Each
 *       argument can either have a string value, or a list array of strings,
 *       where the list array is used for multi-line values.
 *   MCP_SUPPORTED ( intDescr strPkgName -- fltVersion )
 *       Returns the version number of this package that is supported by this
 *       connection descriptor.  If this package isn't supported, returns 0.0
 *       The version number is represented as a floating point number, with the
 *       minor version number being divided by 1000.  For example, an MCP
 *       package of version 1.1 is represented as 1.001, and a version of 1.23
 *       is represented as 1.023.  This lets you use mathematical compares to
 *       check version numbers.
 *   MCP_SEND ( intDescr strPkgName strMsgName dictArgs -- )
 *       Sends an MCP message for the given package to the given connection
 *       descriptor.  dictArgs contains key-value pairs, where each key is
 *       an argument name, and the value is the argument value.  Values can
 *       be strings, floats, dbrefs, integers, or array lists of strings.
 *       They all get translated into an appropriate string format before
 *       getting sent.
 *
 *
 *
 *
 * 2.2fb6.00a20
 * Changed the packaging scripts to preserve modification dates on source files.
 * Changed all calls to set_property() to be 64 bit clean.
 * Fixed a bug in the debugger's "prim" command.
 * Fixed an error that excluded topwords.c from the release packages.
 * Fixed a crasher bug with 63 & 64 character filenames in the data/info dir.
 * Added ARRAY_NOTIFY (a1 a2 -- ) muf primitive.  a1 is an array of strings to
 *   notify to all the dbrefs in array a2.
 *
 *
 *
 * 2.2fb6.00a19
 * Added ARRAY_NUNION ({a} -- a) MUF prim, to return a list array, containing the
 *   union of values of all the given arrays.
 * Added ARRAY_NINTERSECT ({a} -- a) prim, to return a list array, containing the
 *   intersection of all the given arrays.  Multiple arrays are consecutively
 *   processed against the results of the previous intersection, from the top of
 *   the stack down.
 * Added ARRAY_NDIFF ({a} -- a) MUF prim, to return a list array, containing the
 *   difference of all the given arrays.  Multiple arrays are consecutively
 *   processed against the results of the previous difference, from the top of
 *   the stack down.
 * Added SRAND ( -- i ) to muf.  Generates a seeded random number.
 * Added SETSEED ( s -- ) to muf.  Sets the seed for SRAND.  Only the first
 *   thirty-two characters are significant.  If SRAND is called before SETSEED
 *   is called, then SRAND is seeded with a semi-random value.
 * Added GETSEED ( -- s ) to muf.  Returns the the current SRAND seed string.
 * Fixed bug with compiling under Linux using glibc2.
 * Updated configure script using a much newer autoconf program.
 *
 *
 *
 * 2.2fb6.00a18
 * Added FOREACH ( a -- @ ? ) as a loop start construct.  Use similar to FOR.
 * Added ARRAY? ( ? -- i ) to test if a stack item is an array.
 * Added DICTIONARY? ( ? -- i ) to test if a stack item is a dictionary array.
 *
 *
 *
 * 2.2fb6.00a17
 * Fixed a crasher bug with FORKing a muf process with any scoped vars.
 * Changed MUF time related primitives to be cleaner under 64 bit systems.
 * Added ARRAY stack item type to MUF.
 * Added the following primitives:  (@ represents an index int, string, or float)
 *   ARRAY_MAKE       ( {?} -- a )   Makes a list array from a stackrange.
 *   ARRAY_MAKE_DICT  ( {@ ?} -- a ) Makes a dictionary associative array from
 *                                     a stackrange of index/value pairs.
 *   ARRAY_EXPLODE    ( a -- {@ ?} ) Explodes array into stackrange of index/value
 *                                     pairs. ie:  "idx0" "val0" "idx1" "val1" 2
 *   ARRAY_KEYS       ( a -- {@} )   Returns the keys of an array in a stackrange.
 *   ARRAY_VALS       ( a -- {?} )   Returns the vals of an array in a stackrange.
 *   ARRAY_COUNT      ( a -- i )     Returns count of items in array
 *   ARRAY_FIRST      ( a -- @ i )   Returns first index in array, and a boolean.
 *                                     Bool is false if no items are in array.
 *   ARRAY_LAST       ( a -- @ i )   Returns last index in array, and a boolean.
 *                                     Bool is false if no items are in array.
 *   ARRAY_PREV       ( a @ -- @ i ) Returns previous index in array, & a boolean.
 *                                     Bool is false if no items left.
 *   ARRAY_NEXT       ( a @ -- @ i ) Returns next index in array, and a boolean.
 *                                     Bool is false if no items left.
 *   ARRAY_GETITEM    ( a @ -- ? )   Gets a given item from an array.
 *   ARRAY_DELITEM    ( a @ -- a' )  Removes a given item from an array.
 *   ARRAY_SETITEM    ( ? a @ -- a') Overwrites a given array item with value
 *   ARRAY_INSERTITEM ( ? a @ -- a') Inserts a given value into an array.
 *   ARRAY_GETRANGE  ( a @ @ -- a' ) Gets range between two indexes (inclusive)
 *                                     from an array, returning it as an array.
 *   ARRAY_DELRANGE  ( a @ @ -- a' ) Deletes a range of items from an array,
 *                                     between two indexes, inclusive. Returns
 *                                     the resulting array.
 *   ARRAY_SETRANGE  (a1 @ a2 -- a') Sets items in list a1 to vals from list a2,
 *                                     starting at the given index.  Returns the
 *                                     resulting array.
 *   ARRAY_INSERTRANGE (a1 @ a2 -- a') Inserts items from array a2 into a1,
 *                       starting at the given index.  Returns
 *                       the resulting array.
 *
 *
 *
 * 2.2fb6.00a16
 * Added PMATCH (s -- d) prim to MUF to avoid costly calls to wizbit libraries.
 * Added function-scoped variables to MUF.  They are local to each invocation
 *   of the given function, and recursive calls will get their own scoped vars.
 *   You declare a function-scoped var by using 'var VARNAME' inside a function.
 *
 *
 *
 * 2.2fb6.00a15
 * Fixed a bug in popn that caused wierd system behaviour.
 * Fixed a crasher bug in dupn.  Similar to the dup bug fixed recently.
 * Fixed a crasher bug in ldup.  Similar to the dup bug fixed recently.
 * Changed ldup and dupn to accept 0 as a valid value.
 *
 *
 *
 * 2.2fb6.00a14
 * Fixed a few bugs where some changed objects would fail to get delta dumped
 *   under certain circumstances.
 *
 *
 *
 * 2.2fb6.00a13
 * Fixed a crasher bug with the newobject primitive.
 * Fixed a crasher bug with the copyobj primitive.
 *
 *
 *
 * 2.2fb6.00a12
 * Fixed a crasher bug with doing a pop in the muf debugger on an empty stack.
 *
 *
 *
 * 2.2fb6.00a11
 * Changed all references to THING specific structures to go through macros.
 * Fixed (I think) a crasher bug with @forcing zombies and vehicles.
 *
 *
 *
 * 2.2fb6.00a10
 * Added patches to allow entry of empty lines.
 * Fixed crasher bugs in MUF compiler with empty lines.
 * Fixed a bug with the MPI {links} command regarding metalinks.
 * Fixed many small memory leaks.
 * Fixed a crasher in @pcreate caused by player specific struct mods.
 *
 *
 *
 * 2.2fb6.00a9
 * Fixed a hanging bug with FOR loops.
 * Fixed a crashing bug with overflowing an omessage string buffer from MPI.
 * Optimized memory usage by allocating structures for player and program specific
 *   data, instead of wasting space in the specific union shared by all objects.
 * Changed all references to player or program specific data to go through macros.
 * Changed {otell} to fix restrictions on nameless messages.
 *
 *
 *
 * 2.2fb6.00a8
 * Fixed a crashing bug in freeing of unused propdirs, with propdirs diskbasing.
 * Fixed a crasher bug in MPI caused by a buffer overflow.
 * Fixed a bug in announce when not using IPV6.
 * Fixed a string termination bug in with '@mpi {foo'
 * Fixed a bug where DESCR_SETUSER wasn't checking for stack underflow correctly.
 * Fixed a bug in freeing unused propdirs from memory.  This _might_ fix the bug
 *   with losing entire propdirs of properties after the first deltadump. [Nope.]
 * Fixed a bug with _listen programs that SLEEP.  This might fix the "Tried to
 *   free an already freed program frame" crasher bug. (Thanks, Fre'ta!)
 * Fixed the restart script to be more friendly to having multiple mucks on the
 *   same machine.  It now uses the netmuck.pid file to determine if a particular
 *   muck is running from a particular directory, from a particular account,
 *   instead of just greping for all 'netmuck' programs running on the machine.
 * Edited edit-help.txt slightly for formatting, and corrected a slight error.
 * Added rwho_inet_addr() to rwho.c to fix lack of portability with inet_addr().
 * Added -version command line option, to see what version the server binary is.
 * Added -gamedir command line option.  Server cd's to this dir before starting.
 * Added -dbin, -dbout, and -port command line options for specifying the input
 *   and output db files, and the port number.  This is an alternative to the old
 *   syntax of 'netmuck infile outfile portnum'.
 * Added GETLINKS ( d -- dn..d1 n ) muf primitive, for getting info on metalinks.
 *   Returns 0 when the obj is an unlinked exit, or if the obj is a program.
 *   Returns 0 if the obj is a room with no dropto.  Returns #-3 and a count of 1
 *   if the dropto is linked to HOME.
 * Optimized database dumping slightly.
 * Changed {list} and {lexec} to return a null string if the list wasn't found.
 *   ie: they no longer error out with a "Failed list read."
 *
 *
 *
 * 2.2fb6.00a7
 * Added USE_IPV6 #define option to config.h, to allow support for the future
 *   IP version 6 Internet Protocol.  The code for IPv6 support was contributed
 *   by Kim Liu.
 * Added NEXTOWNED (d -- d) primitive to MUF.  When called with a player dbref,
 *   this returns the dbref of the first object they own.  When called with that
 *   dbref, this returns the next object owned by the same player.  When there
 *   are no more objects left owned by that player, then #-1 is returned.  The
 *   order of the objects is not guarenteed, but when used correctly, each object
 *   owned by that player will be returned exactly once.  The player object itself
 *   will NOT be returned.  This is used similarly to the NEXT primitive.  Ex:
 *       me @ begin dup while dup unparseobj .tell nextowned repeat
 * Added LDUP ( {?} -- {?} {?} ) to duplicate a stackrange on top of the stack.
 * Added DUPN ( ?n...?1 i -- ?n...?1 ?n...?1 ) to duplicate the top N stack items.
 * Added POPN ( ?n...?1 i -- ) to pop the top N stack items.
 * Added LREVERSE ( ?n...?1 i -- ?1...?n i ) reverses top N items, leaving count.
 * Changed REVERSE back to ( ?n...?1 i -- ?1...?n )  ie: no count left on top.
 * Replaced edit-help.txt with a more understandable editor help screen.
 *
 *
 *
 * 2.2fb6.00a6
 * Fixed a crasher bug with propdir based diskbasing.
 * Changed DB dumping routines to free unused propdirs from memory after saving.
 * Documented {default} in mpihelp.txt.
 * Changed ITOC primitive to allow creating an escape char.
 *
 *
 *
 * 2.2fb6.00a5
 * Added boolean @tune option for diskbase_propdirs to enable propdir diskbasing.
 * Added ability to diskbase by propdirs.  This means that the server only loads
 *   properties that are in propdirs that are being accessed.  Hopefully this will
 *   reduce the memory usage of FB.
 * Fixed bug with INTOSTR not correctly handling negative numbers,
 * Fixed loophole in {otell} that allowed spoofing.
 * Fixed some minor bugs in MPI list and looping functions, to correctly return
 *   empty initial list items.
 * Fixed {parse} to deal correctly with a null output separator.
 * Changed MUF debugger to make it always print line numbers before souce code.
 * Changed REVERSE primitive to keep the count: ( ?n ... ?1 N -- ?1 ... ?n N )
 *   To obtain the old behavior, just pop off the count.
 * Changed {otell} and {tell} to allow _listeners to hear them.
 * Changed MUF's NAME and TRUENAME prims to return "<garbage>" on recycled objs.
 *
 *
 *
 *
 * 2.2fb6.00a4
 * Fixed math bug in ROUND that rounded 1.5000 down to 1.0.
 * Fixed bug where MUF debug trace would print 1.000 as 1 without decimal point.
 * Fixed range checking bugs in several floating point MUF primitives.
 * Changed FTOSTR to always include a decimal point.
 * Added REVERSE (?n ... ?1 n -- ?1 ... ?n) MUF primitive.  Reverses the stack
 *   order of the top n stack items.
 * Added %~ format code to FMTSTRING.  Will take any stack item type and output
 *   the default format representation for that type.  If passed a float, the
 *   format "%12.8~" will act like "%12.8g".  If passed a string, it will act
 *   like "%12.8s".  Et cetera.
 * Changed ROUND MUF primitive to take a float and an integer argument, the
 *   integer setting the 'precision' of the rounding in decimal places.
 *
 *
 *
 * 2.2fb6.00a3
 * Changed examine code to display Haven flag on Things as HIDE, since it's used
 *   on objects of type Thing to hide the contents when you look at them.
 * Added {ESCAPE:text} MPI function.  Lets you keep {eval:{escape:{&arg}}} from
 *   evaluating any MPI code that the user may have entered.  Basically quotes
 *   and escapes text so that when evaluated, the original text is returned.
 * Added DESCRFLUSH (i -- ) to MUF.  Flushes output text on the given descriptor.
 *   If -1 is passed as the descriptor, it flushes output on all connections.
 * Added calls to sync() after database dumps to make sure the databases are
 *   physically saved to disk quickly after a dump.
 *
 * ----------------------START Mods by Points -----------------------
 * Programmer's notes for 6.00 MUF primitive additions.
 * Additions and notes by Points.
 *
 * Major changes:
 *
 *   In this version, a number of changes and additions have been made to
 * the MUF server.  MUF now supports a new type, floating point, as well
 * as hosts a variety of new primitives in several categories.  A
 * floating point library has been created.  To support this, a number of
 * new property handling primitives have been creates and modified to
 * allow float-types to be stored to and read from props.  In addition,
 * the new math library supports range error checking.  The old integer
 * math library has been expanded and now uses the new error routines as
 * well.  Finally, a handful of new string operations have been added to
 * both speed up string manipulations as well as make some basic
 * manipulations much easier for the programmer.
 *
 * Floating Point:
 *
 *   The following floating-point math functions have been added -
 *         CEIL - returns the next highest integer number (as floating point).
 *         FLOOR - returns the next lowest integer number (as floating point).
 *         FLOAT - converts an integer into a floating point number.
 *         SQRT - gives a square root.
 *         POW - returns x to the power of y.
 *         FRAND - returns a random floating point number between 0 and 1.
 *         SIN - returns the sine of a number.
 *         COS - returns the cosine of a number.
 *         TAN - returns the tangent of a number.
 *         ASIN - returns the inverse sine of a number.
 *         ACOS - returns the inverse cosine of a number.
 *         ATAN - returns the inverse tangent of a number.
 *         EXP - returns the value of e raised to the x power.
 *         LOG - returns the natural log of a number.
 *         LOG10 - returns the log base 10 of a number.
 *         FABS - returns the absolute value of a number.
 *         STRTOF - converts a string to a floating point value.
 *         FTOSTR - converts a floating point value to a string.
 *         FMOD - floating point remainder of x/y.
 *         MODF - Returns the integral and fractional parts of x, both as
 *                 floating point values.
 *         PI - gives PI.
 *         INF - returns an infinite result.
 *         ROUND - rounds to the nearest integer, returned as a floating
 *                 point value.
 *
 *   Related functions -
 *         GETPROPFVAL - retrieves a float value stored in a property.
 *         FLOAT? - returns true if the next item on the stack is a
 *                 floating point value.
 *
 *   Some notes regarding range -
 *         SIN, COS and TAN only operate in the ranges between -pi/4 and
 * pi/4.  It may be nessecary for the programmer to have to check these
 * values and set the sign as appropriate after processing.  ASIN and
 * ATAN only operate in the ranges between -pi/2 and pi/2 while ACOS
 * operates within the range of 0 to pi.  Most functions will not accept
 * INF as a legal input.  SQRT expects a value greater than or equal to
 * zero.  LOG and LOG10 require a value greater than zero.  Very small
 * values will return INF.  Finally, POW requires that for x^y, if x is
 * zero, y must be greater than 0, and if x is less than zero, y must be
 * an integer value.
 *
 *   Some notes regarding string formatting -
 *         STRTOF recognizes most standard forms of floating point
 * notation.  This includes the xxx.yyy format as well as the x.yyyEzz
 * forms.  Conversely, FTOSTR can return either form, depending on which
 * will contain the fewer number of characters for the given value.  Use
 * FMTSTRING (see below) to fix the output style.
 *
 * Other math changes:
 *
 *   For the standard math functions (+,-,/,*,etc.), the following types
 * are allowed -
 *         x       OP      y       result
 *        -------------------------------
 *         INT             INT     INT
 *         DBREF           INT     DBREF
 *         VAR             INT     VAR
 *         LVAR            INT     LVAR
 *         FLOAT           FLOAT   FLOAT
 *         FLOAT           INT     FLOAT
 *         INT             FLOAT   FLOAT
 *
 *   FLOAT types are not allowed to be used in the MOD command.
 *   All bit operations on FLOAT types will be converted to INT types.
 *   It is no longer nessevary to use DBCMP to compare for equality
 * between two differnet dbref numbers.  Dbrefs can now use the standard
 * comparison operations (>,<,=,>=,<=).  DBCMP has been retained for
 * backwards compatibility.
 *   INT will convert FLOAT types to INT as well as DBREF, VAR and LVAR
 * types.  In the cases of VAR and LVAR, INT will return the index number
 * of the variable.
 *
 * Math error functions:
 *
 *   The new MUF math functions now report when certain math errors have
 * occurred.  Among these errors would be such items as division by zero,
 * overflow, underflow, using INF as an input or input values out of
 * range.  In most cases, an error condition will return a zero value
 * (except in the case of integer math, which will wrap around on an
 * overflow or underflow condition).  It is possible to poll for error
 * conditions after every math operation, or when a '0' result is found.
 *
 *   The error primitives are -
 *         CLEAR - this clears all error flags.
 *         CLEAR_ERROR - this will clear a specific error flag.
 *         ERROR? - will return true if any error flags have been set.
 *         SET_ERROR - sets a specific error flag on.
 *         IS_SET? - checks to see if a specific error flag is set.
 *         ERROR_STR - given an error identifier, returns a user-readable error
 *                 string.
 *         ERROR_NAME - given the error flag bit identifier, returns the string
 *                 name for the error flag.
 *         ERROR_BIT - given the error flag string name, returns the bit
 *                 identifier.
 *         ERROR_NUM - returns the total number of error flag types.
 *
 *   The current error flags supported are -
 *         DIV_ZERO  - (0) Division by zero attempted.
 *         NAN       - (1) Result was not a number.
 *         IMAGINARY - (2) Result would be imaginary.
 *         FBOUNDS   - (3) Floating-point inputs were out of range.
 *         IBOUNDS   - (4) Calculation resulted in an integer overflow or
 *                         underflow.
 *
 * New string functions:
 *
 *   The new string primitives are -
 *         TREAD - acts like a timed READ call.  If the user does not provide
 *                 input within the given number of seconds, the READ call will
 *                 time-out and return a failure to the program, otherwise it
 *                 returns a success and the string value entered.
 *         MIDSTR - returns the string specified from within a given string.
 *         CTOI - converts a character (first character in a string) to its
 *                 ASCII equivilent.
 *         ITOC - converts an integer to its ASCII equivilent character.  If it
 *                 is not a valid display character, a null string is returned.
 *         STOD - takes a string and attempts to extract a dbref number from it.
 *                 Recognizes both plain numbers as well as numbers prepended
 *                 with the '#' sign.
 *         SPLIT - given a string and a string token, will split the first string
 *                 at the first found instance of the token.  The split string
 *                 will be the original string and a null if no token matches.
 *         RSPLIT - as SPLIT, but finds the last matching token.
 *         FMTSTRING - allows for string formatting with format substitutions as
 *                 per C's printf.  See below for further implementation details.
 *
 *   FMTSTRING usage -
 *         FMTSTRING can be used to format complicated and long strings, as well
 *                 as multi-lined (with embedded new-lines) strings.  These
 *                 strings can consist entirely of user-specified text, formatted
 *                 variable entries (as values taken from the stack) or a
 *                 combination of both.
 *
 *   The syntax for the format string is as follows:
 *
 *   Format -+---+-%[-,|][+, ][0][number][.number]type->+----->
 *           ^   |                                      |
 *           |   +-text-------------------------------->|
 *           |                                          |
 *           +------------------------------------------+
 *
 *   Here, text can be any string that does not contain a '%'.  This can
 * be circumvented by replacing any occurance of a '%' with '%%'.  'Number'
 * is any standard integer number, and type should be one of the following
 * single character identifiers (case is important):
 *
 *         i - integer argument
 *         s - string argument
 *         ? - unknown type argument, will print a string stating what the
 *             variable type is
 *         d - dbref number, in the form of #123
 *         D - dbref name reference; given a dbref, will print the associated
 *             name for that object - terminates on bad reference
 *         l - pretty-lock, given a lock, will print the description
 *         f - float in xxx.yyy form
 *         e - float in x.yyEzz form
 *         g - shorter of forms e or f
 *
 *   A sample format string might look something like:
 *
 *         "There are %i apples in the box."
 *
 *   If there was an integer value of '5' on the stack, this would return:
 *
 *         "There are 5 apples in the box."
 *
 *   Variables can be formatted in very specific manners.  For numeric
 * entries, zero padding can be specified, as well as control over the
 * sign field.  The total output field size for the variable can be
 * specified, as well as the minimum and maximum output lengths.  Within
 * a field, output can be left, right or center justified.  The [-,|]
 * denotes the justification style to use.  With no argument, a field will
 * be right justified.  A '-' will change this to left and a '|' will make
 * the field centered.  If justification is to be used, the first
 * numeric entry must be specified.  This denotes the total size of the
 * variable field.  If the output of the variable is not limited by the
 * maximum output number (see below), and the total size of the output is
 * greater than the given field width, justification will have no meaning.
 * The second number field (after the period) specifies the maximum number
 * of characters to be printed for string variables, or the precision for
 * numerics.  When dealing with numerics, the '+', ' ' and '0' characters
 * also can be used before the numeric fields.  Specifing '+' will make
 * sure that a sign character is always printed before the number, wether
 * it be a plus or a minus.  Default is to only print a minus sign as
 * needed.  If a ' ' is used instead of the '+', a positive number will
 * be prefaced with a space instead of a plus-sign.  When a '0' is given,
 * zeros will be prefaced to the printed number in order to fill the
 * field width.
 *   Tabbing and new-lines are allowed within the format strings as well.
 * Tabs are defaulted to the equivilent of eight spaces.  Starting a new
 * line with '\r' will reset the tab count.  Unless explicitly reset with
 * a new-line character, tab will continue to count in mod-eight across
 * the given output line.  To insert a tab character, use '\t'.
 *   Variables should be on the stack 'under' the format string, and should
 * be in order of reference.  The first variable referenced by the format
 * string should be the next item in the stack, and so forth.
 *
 * Primitive prototypes:
 *
 *         CEIL    [ f - f ]
 *         FLOOR   [ f - f ]
 *         FLOAT   [ i - f ]
 *         SQRT    [ f - f ]
 *         POW     [ f f - f ]
 *         FRAND   [ - f ]
 *         SIN     [ f - f ]
 *         COS     [ f - f ]
 *         TAN     [ f - f ]
 *         ASIN    [ f - f ]
 *         ACOS    [ f - f ]
 *         ATAN    [ f - f ]
 *         EXP     [ f - f ]
 *         LOG     [ f - f ]
 *         LOG10   [ f - f ]
 *         FABS    [ f - f ]
 *         STRTOF  [ s - f ]
 *         FTOSTR  [ f - s ]
 *         FMOD    [ f f - f ]
 *         MODF    [ f - f f ]
 *         PI      [ - f ]
 *         INF     [ - f ]
 *         ROUND   [ f - f ]
 *         GETPROPFVAL [ d s - f ]
 *         FLOAT?  [ ? - i ]
 *         CLEAR   [ - ]
 *         CLEAR_ERROR [ s|i - i ]
 *         ERROR?  [ - i ]
 *         SET_ERROR [ s|i - i ]
 *         IS_SET? [ s|i - i ]
 *         ERROR_STR [ s|i - s ]
 *         ERROR_NAME [ i - s ]
 *         ERROR_BIT [ s - i ]
 *         ERROR_NUM [ - i ]
 *         TREAD   [ i - s i ]
 *         MIDSTR  [ s i i - s ]
 *         CTOI    [ s - i ]
 *         ITOC    [ i - s ]
 *         STOD    [ s - d ]
 *         SPLIT   [ s s - s s ]
 *         RSPLIT  [ s s - s s ]
 *         FMTSTRING [ ?1 ... ?n s - s ]
 *
 * All changes completed as of 10/1/96.
 * ----------------------END Mods by Points --------------------------
 *
 *
 *
 *
 * 2.2fb5.56b
 * Fixed a bug in {testlock} that always tested the lock against the using player,
 *   regardless of who it was told to test against.
 * Optimized the MUF INTOSTR primitive to be faster and more efficient.
 * Optimized the MUF CON* primitives to be faster and more efficient.
 * Optimized property trees to remove redundant searches and unneeded recursion.
 * Optimized fetching of property values from disk.
 * Added the DIM attribute option to {attr} and TEXTATTR
 *
 *
 *
 * 2.2fb5.56a
 *
 * Fixed compile bugs when GOD_PRIV was undefined.
 *
 * Changed permissions on {istype} to make it only match local objects.
 *
 * Various changes to man.txt, including very brief docs on the muf debugger.
 *
 * Added FOR (i1 i2 i3 -- i) MUF loop, to loop from i1 to i2, with a step of
 *   i3.  The current count is pushed onto the stack at each iteration.  FOR is
 *   used just like BEGIN, marking the beginning of a loop, with REPEAT or
 *   UNTIL marking the end.  However unlike other loops, FOR loops are
 *   limited to a ridiculously high nesting of 512, enforced at runtime.
 *   The FOR primitive is actually (i1 i2 i3 -- ) and the FORITER primitive,
 *   used to control the iteration count is ( -- [i] i1) where i1 is a
 *   boolean signaling weather or not to continue, and if continuing, i is
 *   the currnet count.  The primitive FORPOP ( -- ) cleans up the FOR
 *   nesting stack by popping off the data for the nested loop.
 *
 * Fixed a bug where a reference to a loop right after the BEGIN would cause
 *   either a MUF error in the case of a non-nested loop, or incorrect code,
 *   in the case of a nested loop.
 *
 * Made the MUF compiler less recursive and more iterative.
 *
 * Added reporting of file:line when an instruction that has been CLEAR()ed
 *   is unparsed for display.
 *
 * Added ANSI color ability to the server.  Players only see the ANSI codes if
 *   they have their COLOR bit set.  To add an escape sequence to a string, use
 *   \[ to represent the escape char.  (Similar to \r for carriage returns.)
 *   This works in both MUF and in MPI.  Only color, bold, underline, reverse,
 *   and flash attributes are allowed.  All other escape sequences are stripped.
 *
 * Added the {attr:} function to MPI, to allow setting attributes of text for
 *   players who have clients that can display them.  The syntax for the {attr}
 *   function is:  {attr:ATTRIBUTE,...,TEXT} where you may specify up to eight
 *   attributes to give to the specified TEXT.  Ie:: {attr:bold,red,WARNING!}
 *   would print WARNING! in bold red text, then reset back to the default text
 *   style for anything after the {attr:} command.  {ATTR} commands do not nest
 *   well, yet, so don't put {ATTR}s inside other {ATTR}s.
 *
 * Added TEXTATTR (textstr attrstr -- codedstr) command to MUF.  Takes a plain
 *   text string and adds the neccesary codes to make the output codedstr display
 *   with the given attributes, when shown with an appropriate client.  The attri-
 *   butes are passed to TEXTATTR in the attrstr, as a series of comma separated
 *   attribute names. ie:  "WARNING!" "bold,red" TEXTATTR ME @ SWAP NOTIFY
 *
 *   The attributes supported by the MPI {ATTR} function and the MUF TEXTATTR
 *   command are: reset, bold, flash, underline, reverse, black, magenta, red,
 *   yellow, green, cyan, blue, white, bg_black, bg_magenta, bg_red, bg_yellow,
 *   bg_green, bg_cyan, bg_blue, or bg_white.  The bg_* series of attributes set
 *   the background color.  The colors without the bg_ prefix set the foreground
 *   color attributes.  Reset will reset the text attributes back to normal.
 *
 *   It is best to use {ATTR} or TEXTATTR instead of directly making ANSI escape
 *   codes with \[, since it is planned to make {ATTR} and TEXTATTR optionally
 *   send HTML codes instead of escape sequences, for those client programs what
 *   will be able to use it.  Besides, it's easier to read {attr:bold,text}
 *   instead of \[[1mtext.
 *
 * Changed name setting code to always reject putting escape chars in names.
 *
 * Fixed a bug with compiling under Linux with DETACH defined.
 *
 * Fixed a sporatic crasher bug that ocurred when the number of processes on the
 *   timequeue was exactly ten, and all were due.
 *
 * Revision 1.7  2001/09/17 13:26:00  points
 * For MUF: Fixed problems with updating last_used on objects when only
 * exits, contents or name was checked.  This was inconsistent use.  MUF
 * will only update last_used now if a moveto occurs.
 * Other: parenting loop check has now been added with an emegency escape
 * to #0 when a loop can not be avoided.  Loop check has been made linear
 * instead of recursive, and better handles the potential of 'things' in the
 * envchain.  MAX_PARENT_DEPTH now limits envchain depth.  Extensive testing
 * done, and have not been able to infloop the server anymore.
 *
 * Revision 1.6  2000/11/30 05:26:46  revar
 * Updated TODO file.
 * Changed MAX_OUTPUT from a server #define to an @tune option.
 *
 * Revision 1.5  2000/09/04 22:07:12  winged
 * Added MUD_GID define support code
 *
 * Revision 1.4  2000/07/18 18:18:19  winged
 * Various fixes to support warning-free compiling with -Wall -Wstrict-prototypes -Wno-format -- added single-inclusion capability to all headers.
 *
 * Revision 1.3  2000/03/29 12:21:02  revar
 * Reformatted all code into consistent format.
 * 	Tabs are 4 spaces.
 * 	Indents are one tab.
 * 	Braces are generally K&R style.
 * Added ARRAY_DIFF, ARRAY_INTERSECT and ARRAY_UNION to man.txt.
 * Rewrote restart script as a bourne shell script.
 *
 * Revision 1.2  2000/03/10 06:33:31  revar
 * Added ARRAY_GET_PROPDIRS muf prim.
 * Added ARRAY_GET_PROPVALS muf prim.
 * Added ARRAY_GET_PROPLIST muf prim.
 * Added ARRAY_PUT_PROPVALS muf prim.
 * Added ARRAY_PUT_PROPLIST muf prim.
 * Added PROPLIST_ENTRY_FMT @tune option.
 * Added PROPLIST_COUNTER_FMT @tune option.
 * Reserved IF_TRY and IF_CATCH compiletime structs.
 *
 * Revision 1.1.1.1  1999/12/12 07:28:13  revar
 * Initial Sourceforge checkin, fb6.00a29
 *
 * Revision 1.1.1.1  1999/12/12 07:28:13  foxen
 * Initial FB6 CVS checkin.
 *
 * Revision 1.1  1996/06/17 17:29:45  foxen
 * Initial revision
 *
 * Revision 5.122  1994/01/15  00:08:39  foxen
 * @doing mods.
 *
 * Revision 5.121  1994/01/06  03:51:18  foxen
 * updated version string.
 *
 * Revision 5.12  1994/01/06  03:16:30  foxen
 * Version 5.12
 *
 * Revision 5.1  1993/12/17  00:35:54  foxen
 * initial revision.
 *
 * Revision 1.6  90/09/18  08:06:32  rearl
 * Moved some stuff in from config.h.
 * 
 * Revision 1.5  90/09/13  06:34:46  rearl
 * PROP_PRIVATE added for unreadable properties.
 * 
 * Revision 1.4  90/08/27  14:09:25  rearl
 * Provision for read-only properties: '_' signals these.
 * 
 * Revision 1.3  90/08/09  21:01:21  rearl
 * Took out some useless stuff, fixed tabs.
 * 
 * Revision 1.2  90/07/19  23:14:44  casie
 * Removed log comments from top.
 * 
 * 
 */

#ifndef _PARAMS_H
#define _PARAMS_H

#include "copyright.h"
#include "version.h"

/* penny related stuff */
/* amount of object endowment, based on cost */
#define OBJECT_ENDOWMENT(cost) (((cost)-5)/5)
#define OBJECT_DEPOSIT(endow) ((endow)*5+4)


/* timing stuff */
#define TIME_MINUTE(x)  (60 * (x))	/* 60 seconds */
#define TIME_HOUR(x)    ((x) * (TIME_MINUTE(60)))	/* 60 minutes */
#define TIME_DAY(x)     ((x) * (TIME_HOUR(24)))	/* 24 hours   */


#define DB_INITIAL_SIZE 100		/* initial malloc() size for the db */


/* User interface low level commands */
#define QUIT_COMMAND "QUIT"
#define WHO_COMMAND "WHO"
#define PREFIX_COMMAND "OUTPUTPREFIX"
#define SUFFIX_COMMAND "OUTPUTSUFFIX"

/* Turn this back on when you want MUD to set from root to some user_id */
/* #define MUD_ID "MUCK" */

/* Turn this on when you want MUCK to set to a specific group ID... */
/* #define MUD_GID "MUCK" */

/* Used for breaking out of muf READs or for stopping foreground programs. */
#define BREAK_COMMAND "@Q"

#define EXIT_DELIMITER ';'		/* delimiter for lists of exit aliases  */
#define MAX_LINKS 50			/* maximum number of destinations for an exit */

#define MAX_PARENT_DEPTH 256            /* Maximum parenting depth allowed. */

#define GLOBAL_ENVIRONMENT ((dbref) 0)	/* parent of all rooms.  Always #0 */

/* magic cookies (not chocolate chip) :) */

#define ESCAPE_CHAR 27
#define NOT_TOKEN '!'
#define AND_TOKEN '&'
#define OR_TOKEN '|'
#define LOOKUP_TOKEN '*'
#define REGISTERED_TOKEN '$'
#define NUMBER_TOKEN '#'
#define ARG_DELIMITER '='
#define PROP_DELIMITER ':'
#define PROPDIR_DELIMITER '/'
#define PROP_RDONLY '_'
#define PROP_RDONLY2 '%'
#define PROP_PRIVATE '.'
#define PROP_HIDDEN '@'
#define PROP_SEEONLY '~'

/* magic command cookies (oh me, oh my!) */

#define SAY_TOKEN '"'
#define POSE_TOKEN ':'
#define OVERIDE_TOKEN '!'


/* @edit'or stuff */

#define EXIT_INSERT "."			/* character to exit from insert mode    */
#define INSERT_COMMAND 'i'
#define DELETE_COMMAND 'd'
#define QUIT_EDIT_COMMAND   'q'
#define COMPILE_COMMAND 'c'
#define LIST_COMMAND   'l'
#define EDITOR_HELP_COMMAND 'h'
#define KILL_COMMAND 'k'
#define SHOW_COMMAND 's'
#define SHORTSHOW_COMMAND 'a'
#define VIEW_COMMAND 'v'
#define UNASSEMBLE_COMMAND 'u'
#define NUMBER_COMMAND 'n'
#define PUBLICS_COMMAND 'p'

/* maximum number of arguments */
#define MAX_ARG  2

/* Usage comments:
   Line numbers start from 1, so when an argument variable is equal to 0, it
   means that it is non existent.

   I've chosen to put the parameters before the command, because this should
   more or less make the players get used to the idea of forth coding..     */



/* ANSI attributes and color codes */

#define ANSI_RESET	"\033[0m"

#define ANSI_BOLD	"\033[1m"
#define ANSI_DIM      	"\033[2m"
#define ANSI_UNDERLINE	"\033[4m"
#define ANSI_FLASH	"\033[5m"
#define ANSI_REVERSE	"\033[7m"

#define ANSI_FG_BLACK	"\033[30m"
#define ANSI_FG_RED	"\033[31m"
#define ANSI_FG_YELLOW	"\033[33m"
#define ANSI_FG_GREEN	"\033[32m"
#define ANSI_FG_CYAN	"\033[36m"
#define ANSI_FG_BLUE	"\033[34m"
#define ANSI_FG_MAGENTA	"\033[35m"
#define ANSI_FG_WHITE	"\033[37m"

#define ANSI_BG_BLACK	"\033[40m"
#define ANSI_BG_RED	"\033[41m"
#define ANSI_BG_YELLOW	"\033[43m"
#define ANSI_BG_GREEN	"\033[42m"
#define ANSI_BG_CYAN	"\033[46m"
#define ANSI_BG_BLUE	"\033[44m"
#define ANSI_BG_MAGENTA	"\033[45m"
#define ANSI_BG_WHITE	"\033[47m"

#endif /* _PARAMS_H */
