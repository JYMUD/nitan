#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��������");
        set("long", @LONG
��첽�����˳���������ֻ�����ﲨ�ι��������Ͻ�ˮ��
����ȥ����������һ�鱮(bei)��ǰ�治Զ��������ľ�š�
LONG);
        set("outdoors", "jingzhou");
        set("exits", ([
                "south" : __DIR__"qiao", 
                "north" :__DIR__"nanshilu1",        
        ]));
        set("item_desc", ([
                "bei" : WHT "\n\n\n            ��������������������������������\n"
                        "            ��                            ��\n"
                        "            ��" NOR + HIW "     ͨ      ��      ��" NOR +
                        WHT "     ��\n"
                        "            ��                            ��\n"
                        "            ��������������������������������\n\n\n" NOR,
        ]));
        set("objects", ([
                "/d/beijing/npc/tiaofu" : 2,
        ]));
        set("coor/x", -7100);
	set("coor/y", -2110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}