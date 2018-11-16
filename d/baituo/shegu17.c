// Code of ShenZhou
// shegu.c �߹�
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;
string look_crack();

void create()
{
        set("short", "�߹�����");
        set("long", @LONG
���ǰ���ɽ�߹��е�һ�����֣��Ӳݴ�������ľ֦��ï�ܣ��İ�
��ɭ����ľ�̸���ڣ���Щ��������ѷ�(crack)������ϸ���������
LONG );

        set("exits", ([
            "west" : __DIR__"shegu18",
            "southeast" : __DIR__"shegu16",
        ]));

        set("item_desc", ([
        "crack" : (: look_crack :),
        ]));

        set("objects", ([
            __DIR__"obj/branch"+(1+random(4)) : 1,
        ]));

        set("hide_snake", 1+random(3));
        set("grass", 1);
        set("crack", 1);

        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49940);
        set("coor/y", 20180);
        set("coor/z", 20);
        setup();
}

#include "snake_room.h"