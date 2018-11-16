#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蜀道");
        set("long", @LONG
你走在以险著称天下的蜀道上，道路由东上山，异常难行。由西
而下，然而上山容易下山难，也不见得好走，总之走在这样的路上非
要格外小心，用尽全身气力才行。不多一会儿，你就觉得筋疲力尽了。
LONG );
        set("exits", ([
                  "westup" :  __DIR__"shudao18",
                  "eastdown" : __DIR__"shudao16",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15140);
	set("coor/y", -1830);
	set("coor/z", -10);
	setup();
}

int init()
{
        object me;
        int i;
        me = this_player();
    i=query("max_qi", me)/50;
        me->receive_damage("qi", i);
        tell_object(me, HIR "你费力的走在蜀道上，累的气喘吁吁。\n" NOR);
}