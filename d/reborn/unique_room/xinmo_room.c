// xinmo_room.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIM "��ħ�" NOR);
        set("long", @LONG
�þ��ﵽ���������������ܱߵľ����������ޣ�������翡�
LONG );

        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room",1);
        set("no_clean_up", 1);
        set("outdoors", "maze");
        set("objects", ([
                "/d/reborn/npc/shadow": 5,   
                "/d/reborn/npc/xinmo": 1,   
        ]));
	setup();
}
