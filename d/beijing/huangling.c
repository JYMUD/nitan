#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", HIY"ʮ������"NOR);
        set("long", @LONG
���������������ʮ�����꣬�൱�ĺ�ΰ׳�ۡ�ʮ������������
�Ͻ��ǵ�������������������͵��������ࡣ
LONG );
        set("exits", ([
                "south" : "/d/beijing/guandao_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/youren" : 2,
               "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}