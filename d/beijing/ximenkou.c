#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���ſ�");
        set("long", @LONG
�����Ǿ������ǳǱ߿������ŵ�һ�������Ĵ�����������Ǿ���
���������ˣ���ʵ��̵Ĺų�ǽ�߸������š�ÿ�춼������˾�����
��������뾩�ǡ������Ǿ��ǵ���������֡�
LONG );
        set("exits", ([
                "west" : "/d/beijing/xichengmen",
                "east" : "/d/beijing/bei_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/tiaofu" : 1,
                "/d/beijing/npc/old2" : 1,
                "/d/beijing/npc/tangzi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}