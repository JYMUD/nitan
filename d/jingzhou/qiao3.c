#include <room.h>
inherit ROOM;

void create()
{
        set("short", "��ľ��");
        set("long", @LONG
������һ����ľ�ţ�Ҳ��֪��ʲôʱ��������ģ�������
��ҡҡ�λεģ�����Σ�ա������Ҫ���ӵĻ�����ֻ�������
����������ȥ��ֻ������������һ����ȥ���϶�û����
LONG);
        set("outdoors", "jingzhou");

        set("exits", ([
                "south" : __DIR__"jiangnan", 
                "north"  :__DIR__"qiao2",
        ]));
        set("objects", ([
                "/d/beijing/npc/tangzi" : 1,
        ]));
        set("coor/x", -7100);
	set("coor/y", -2140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}