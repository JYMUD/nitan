// Room: /d/quanzhou/jiangjunfu1.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "�������鷿");
        set("long", @LONG
���Ǿ�������鷿����������鼮֮�⣬����Ļ��Ǹ��ֱ��С�
LONG );
        set("exits", ([
                "south" : __DIR__"jiangjunfu",
        ]));
        set("objects", ([
                __DIR__"npc/shi" : 1,
        ]));
	set("coor/x", -880);
	set("coor/y", -7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}