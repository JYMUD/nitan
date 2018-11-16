// wuchang1.c 武场
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "武场");
        set("long", @LONG
这里是全真教的演武场，地下的青砖本来铺的整整齐齐，却
不知道被谁踩出了几十个大大小小的凹坑。看的出来，这里成年
累月的有弟子修炼掌法步法，天长日久，地下就踩出了凹坑。
LONG
        );
        set("outdoors", "chongyang");
        set("exits", ([
                "south" : __DIR__"wuchang2",
                "north" : __DIR__"houtang2",
                "southeast" : __DIR__"xiuxishi",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2750);
        set("coor/y", 100);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}