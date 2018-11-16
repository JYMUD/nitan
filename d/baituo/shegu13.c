// Code of ShenZhou
// shegu.c �߹�
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;
string look_bush();

void create()
{
        set("short", "�߹�����");
        set("long", @LONG
���ǰ���ɽ���߹�֮�У����������ŴԴ԰���(bush)�����ض���
�ӲݺͿ�֦��Ҷ����ζ������š�С·���۵ش������ԣ���֪��ͨ��
���
LONG );

        set("exits", ([
            "east" : __DIR__"shegu14",
            "southwest" : __DIR__"shegu6",
        ]));

        set("item_desc", ([
        "bush" : (: look_bush :),
        ]));

        set("objects", ([
            __DIR__"obj/branch"+(1+random(2)) : 1,
            __DIR__"obj/branch"+(3+random(2)) : 1,
        ]));

        set("hide_snake", random(3));
        set("grass", 1);
        set("bush", 1);

        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49980);
        set("coor/y", 20170);
        set("coor/z", 20);
        setup();
}

#include "snake_room.h"