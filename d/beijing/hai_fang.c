#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�᷿");
        set("long", @LONG
�����Ǻ��ι���������һ���᷿���������ι����Ŀ��˾�ס��
LONG );
        set("exits", ([
                "east" : "/d/beijing/hai_dayuan",
        ]));

        set("sleep_room", "1");
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7630);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}