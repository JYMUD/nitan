// Code of ShenZhou
// shegu.c �߹�
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�߹�����");
        set("long", @LONG
���ǰ���ɽ���߹�֮�У���ľ����������һƬ���ס�
LONG );

        set("exits", ([ 
            "north" : __DIR__"shegu26",
            "southwest" : __DIR__"shegu_maze4",
        ]));

        set("cost", 1);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49980);
        set("coor/y", 20210);
        set("coor/z", 20);
        setup();
}

void init()
{
        set("enter_shegu", 1, this_player());
}