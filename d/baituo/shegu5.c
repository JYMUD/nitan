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
�ƺ���ʲ���ڲ������شܶ��������ߵ���ľ�ƺ��Ƚ�ϡ�١�
LONG );

        set("exits", ([
                "southeast" : __DIR__"shegu4",
                "northwest" : __DIR__"shegu6",
        ]));

        set("objects", ([
                __DIR__"obj/branch2" : 1,
                __DIR__"npc/maque" : 2,
        ]));

        set("hide_snake", random(3));
        set("grass", 1);

        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49980);
        set("coor/y", 20150);
        set("coor/z", 20);
        setup();
}

#include "snake_room.h"