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
                "south" : __DIR__"qiao3", 
                "north"  :__DIR__"qiao",
        ]));
        set("objects", ([
                "/d/beijing/npc/old1" : 1,
                "/d/beijing/npc/girl3" : 1,
        ]));
        set("coor/x", -7100);
	set("coor/y", -2130);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}