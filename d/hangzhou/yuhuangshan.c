// yuhuangshan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "���ɽ");
        set("long", @LONG
ɽ����һ��Сͤ������ͤ�������ο͵�ɽǰ����ɽ�ᶼ�ڴ�СЪ��
ɽ·�����������ϡ�������һ����·��
LONG);
        set("exits", ([
            "eastup"  : __DIR__"shanlu6",
            "west"    : __DIR__"road18",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 760);
	set("coor/y", -2100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}