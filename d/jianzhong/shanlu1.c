// Room: /d/jianzhong/qzroad1.c

#include <room.h>
inherit BUNCH_ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
������һ��ɽ·�ϡ�·�Ե�ɽ����ϡϡ����س��ż�������
LONG
        );

        set("exits", ([
                "southwest" : "/d/xiangyang/eastgate2",
                "east" : __DIR__"shanlu2",
        ]));

        set("outdoors", "jianzhong");
        set("coor/x", -430);
        set("coor/y", -500);
        set("coor/z", 0);
        setup();
}
