#include <room.h>
inherit ROOM;

void create()
{
        set("short", "回春堂藥店");
        set("long", @LONG
回春堂藥店是整個北京城裡最大最有名氣的藥鋪。你還沒走進這
里，便聞到一股濃濃的藥材氣味，那是從葯柜上的幾百個小抽屜里散
發出來的。一位夥計在櫃檯後站着，堆着笑臉招呼着客人。
LONG );
       set("exits", ([
                "west" : "/d/beijing/xi_2",
                "east" : "/d/beijing/liandan_neiting",
        ]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
                "/d/beijing/npc/yaopuhuoji" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}