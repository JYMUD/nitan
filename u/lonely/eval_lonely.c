
// This file is made by the "eval" command.

#include <ansi.h>
#include <command.h>
#include <function.h>
#include <localtime.h>
#include <origin.h>
#include <room.h>
#include <type.h>
#include <user.h>
#include <eval.h> 

inherit F_CLEAN_UP;

mixed eval(string euid)
{
        seteuid(euid);
                {
	"/cmds/std/look.c"->main(me, "lonely");
	}
}
