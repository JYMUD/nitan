#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "ׯ������");
        set("long", @LONG
����һ�����ã����Ϲ����߰˸���λ������һ�������Ϲ�����һ
�����ˡ�
LONG );
    set("exits", ([
        "east" : "/d/beijing/zhuang5",
    ]));
    set("objects", ([
        "/d/shenlong/npc/dizi": 1,
    ]));
    set("outdoors", "beijing");
    set("coor/x", 90);
        set("coor/y", 4720);
        set("coor/z", 0);
        setup();
    replace_program(ROOM); 
}