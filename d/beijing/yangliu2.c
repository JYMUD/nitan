#include <room.h>
inherit ROOM;

void create()
{
        set("short", "������ͬ");
        set("long", @LONG
������������ͬ������ߵ��������Խ���İ�����������խ
��ͨ�����ڲ��ϵ����ϱ����졣
LONG );
       set("exits", ([
                "north" : "/d/beijing/yangliu1",
                "south" : "/d/beijing/yangliu3",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}