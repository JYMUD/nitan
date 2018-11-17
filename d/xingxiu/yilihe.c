// Room: /d/xingxiu/yilihe.c
// Last Modified by winder on Apr. 25 2001

inherit ROOM;
void quarter_pass();

void create()
{
        set("short", "伊犁河");
        set("long", @LONG
伊犁河，位於伊犁城以南，由天山上溶化流下的雪水彙集而成。不
少來往的商旅都將牲口牽至河邊飲水，為下一次的旅途做好準備。河水
清涼透徹，深不及膝。
LONG);

        set("outdoors", "xiyu");
        set("exits", ([
                "southwest" : __DIR__"shanjiao",
                "north"     : __DIR__"yiligate",
        ]));

        set("objects", ([
                 __DIR__"npc/yang" : 1,
                 __DIR__"npc/hgirl" : 1,
        ]));
        set("coor/x", -39000);
        set("coor/y", 11000);
        set("coor/z", 0);
        setup();
//        replace_program(ROOM);
}
#include "/d/xingxiu/job2.h";
