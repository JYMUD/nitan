#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "������");
    set("long", @LONG
������ǵ����շ��߾���Ӣ�ۡ�������������֮�أ���˵������
�������ľ������������߾���ѹ���߶��ڣ����Լ�ȴ�����ػ����߶�
�ڣ��Է��߾��س��˼䡣
LONG);

	set("exits", ([
		"out" : __DIR__"dong2.16",
		"north": __DIR__"shedong3",
		"south":__DIR__"shedong4",
		"west":__DIR__"shedong2",
		
		
		
	]));
	set("objects",  ([
		__DIR__"npc/sai" : 1,
	]));
		
	setup();
	replace_program(ROOM);
}
