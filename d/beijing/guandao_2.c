#include <room.h>
inherit ROOM;

void create()
{
        set("short", "��ٵ�");
        set("long", @LONG
������һ����������Ĵ�ٵ��ϡ���ʱ��������������߷ɳ�
����������һ·��������·��������������������֡�������Զ����
�Ǿ�����������ʤʮ�����ꡣ
LONG );
       set("exits", ([
                "north" : "/d/beijing/huangling",
                "south" : "/d/beijing/guandao_1",
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}