// Room: /d/xiangyang/caodi1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "�ݵ�");
        set("long", @LONG
������������Ĳݵء��ɹű���������������İ���ȫ�����ˣ�
�ɹű��۳���ȥ����Ϊ��������������������š�
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "west"  : __DIR__"northgate2",
                "northup"  : "/d/jueqing/shanjiao",
        ]));
        set("objects", ([
                __DIR__"npc/tuolei"   : 1,
                __DIR__"npc/menggubing" : 2,
        ]));
        set("coor/x", -7800);
	set("coor/y", -710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}