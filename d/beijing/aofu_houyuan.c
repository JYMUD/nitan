inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","������Ժ");
        set("long", @LONG
�����������ĺ�Ժ��������һ����԰������һ�������ߵ�ֱͨ
�����ݵ��鷿������������˽����η��������ɼ�����������������
�š�
LONG );
        set("exits", ([
                "north" :  "/d/beijing/aofu_naofang",
                "west" :  "/d/beijing/aofu_zoulang3",
                "south" :  "/d/beijing/aofu_zoulang2",
        ]));
        set("objects", ([
                "/d/beijing/npc/shi_a" : 2,
        ]));
	set("coor/x", -2820);
	set("coor/y", 7790);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (objectp(present("shi wei", environment(me))) && dir == "north")
                return notify_fail("����������ס�����û����ү�ķԸ���˭Ҳ���ܽ�ȥ��\n\n");
        return ::valid_leave(me, dir);
}