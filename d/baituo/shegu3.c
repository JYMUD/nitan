// shegu.c �߹�
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�߹�ɽ��");
        set("long", @LONG
���ǰ���ɽ�߹��е�ɽ·����һ������ȳ�����С�������ŵ���
����������������С�
LONG );

        set("exits", ([ 
                "southeast" : __DIR__"shegu2",
                "northeast" : __DIR__"shegu4",
        ]));

        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49980);
        set("coor/y", 20130);
        set("coor/z", 20);
        setup();
}

void init()
{
        set("enter_shegu", 1, this_player());
}