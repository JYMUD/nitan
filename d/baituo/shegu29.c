// Code of ShenZhou
// shegu.c �߹�
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;
string look_cave();

void create()
{
        set("short", "ɽ��");

        if(random(3) != 0 ) {
        set("long", @LONG
���ǰ���ɽ���߹�֮�У���������ɽ�ڣ���������ʯ����ʯ����
ϡϡ����س��ż���С�����紵��������ʱ��һЩСʯͷ�ӱ��ϻ���
������
LONG );

                set("item_desc", ([
                "cave" : (: look_cave :),
                ]));

                set("hide_snake", 1);
                set("cave", 1);
        }
        else {
                set("long", @LONG
���ǰ���ɽ���߹�֮�У���������ɽ�ڣ���������ʯ����ʯ����
ϡϡ����س��ż���С�����紵��������ʱ��һЩСʯͷ�ӱ��ϻ���
������
LONG
                );
                set("objects", ([
                __DIR__"obj/stone" : 1,
                __DIR__"npc/lao-shu" : 1,
                ]));
        }

        set("exits", ([
            "northwest" : __DIR__"shegu14",
            "northeast" : __DIR__"shegu28",
        ]));

        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49960);
        set("coor/y", 20160);
        set("coor/z", 20);
        setup();
}

#include "snake_room.h"