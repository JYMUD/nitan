// huangniling.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "������");
        set("long", @LONG
һ������·�������������ܷǳ��İ�����ż���ſ���Щ���˴ҴҶ�����
�ϱ��ֱ�����ɽ��·��
LONG);
        set("exits", ([
            "southdown"   : __DIR__"maojiabu",
            "northdown"   : __DIR__"road3",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
	set("coor/x", 760);
	set("coor/y", -2050);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}