// faxisi.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "��ϲ��");
        set("long", @LONG
��ϲ��������������������ĵ�һ����������οͲ�ʱ�Ľ���
�����������ɴ���������������ɽ��·��
LONG);
        set("exits", ([
                "eastdown"  : __DIR__"shanlu4",
                "northdown" : __DIR__"shanlu3",
        ]));
        set("objects", ([
            __DIR__"npc/guest" : 2,
            __DIR__"npc/seng" : 1,
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 750);
	set("coor/y", -2110);
	set("coor/z", 60);
	setup();
        replace_program(ROOM);
}