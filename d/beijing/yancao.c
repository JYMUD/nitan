#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�̲ݵ�");
        set("long", @LONG
�������������������������˵����ѵ���Ʒ�����������ǳɰ�
��ǧ���ķ�����ȥ���������������е�����ķ�ʽ�����̡�������Զ
��ס�������к������ģ�����������ϰ屻��������ͷ�ϡ������Ĳ�
�������Ǳ�������ġ�
LONG );
       set("exits", ([
                "north" : "/d/beijing/caroad_e2",
        ]));
        set("objects", ([
                "/d/beijing/npc/old2" : 1,
        ]));
        set("outdoors", "beijing");
        set("no_fight",1);
	set("coor/x", -2770);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}