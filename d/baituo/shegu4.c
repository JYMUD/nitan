// shegu.c �߹�
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�߹�ɽ��");
        set("long", @LONG
���ǰ���ɽ�߹��е�ɽ·����һ������ȳ�����С�������ŵ���
����������������С�ɽ·������ľ�������ݴ��в�ʱ����ɳɳ֮����
�ƺ���ʲ���ڲ������شܶ���
LONG );

        set("exits", ([
                "southwest" : __DIR__"shegu3",
                "northwest" : __DIR__"shegu5",
        ]));

        set("objects", ([
                __DIR__"obj/branch"+(1+random(2)) : 1,
                __DIR__"obj/branch"+(3+random(2)) : 1,
                __DIR__"npc/yetu" : 1,
        ]));

        set("hide_snake", random(3));
        set("grass", 1);

        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49970);
        set("coor/y", 20140);
        set("coor/z", 20);
        setup();
}

#include "snake_room.h"