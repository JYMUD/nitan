// shenxudong.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "����");
        set("long", @LONG
�����񷶥�ϵ�ʯ���������һ����⣬��������һ���족����
�ϱ�����ɽ��·��
LONG);
        set("exits", ([
                "southeast" : __DIR__"longhongdong",
        ]));
        set("objects", ([
             __DIR__"npc/mengmian":1,
        ]));
        set("outdoors", "hangzhou");
	set("coor/x", 720);
	set("coor/y", -2060);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}