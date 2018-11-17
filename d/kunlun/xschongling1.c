// Room: /d/kunlun/xschongling1.c
// Last Modified by winder on Jun. 29 2001

inherit ROOM;

void create()
{
        set("short", "雪山叢林");
        set("long", @LONG
這是一個很大的叢林，樹木枝葉上掛滿了冰雪，雪白的一大片，奇
美無比。叢林向山上延伸，直至山頂。在叢林中微露出一條小道，依稀
可認，你走在小道上，雪地中留下一行長長的足印。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
                "westup"    : __DIR__"xuanya",
                "southdown" : __DIR__"xschongling",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "hongmei");
        set("coor/x", -90050);
        set("coor/y", 20010);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}