// chashi.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "����");
        set("long", @LONG
��������������ҡ����������Ʒ�������ʵ�������
LONG);
        set("exits", ([
                "west"     : __DIR__"longjing",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 780);
	set("coor/y", -2100);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}