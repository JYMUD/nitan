// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "����");
        set ("long", @LONG
����һ�����������ȡ������������򸮴��������ߵľ�ͷ�Ǹ�С���á�
LONG);
        set("region", "jingzhou");
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/qifang" : 1,
        ]));
        set("exits", ([
                "south"  : __DIR__"wan_dating",
                "north"  : __DIR__"wan_ketang",
        ]));

        set("coor/x", -7110);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (!objectp(present("hu cheng", me)) &&
                dir == "north" &&
                objectp(present("qi fang", environment(me))))
                return notify_fail("�ݷ���ס��˵���ҷ���ж��Դ���������š�\n");

        return ::valid_leave(me, dir);
}