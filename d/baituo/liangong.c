inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����ǰ���ɽ���ӵ���������������һ���������������Ǹ����ȣ�
��������һ�����ȣ������������ǳ����ɡ�����ɼ�ΡΡ������
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "east"  : __DIR__"fang",
                "north" : __DIR__"menlang",
                "west"  : __DIR__"changlang",
                "south" : __DIR__"dating",
        ]));
        set("objects", ([
                __DIR__"npc/li" : 1,
        ]));
        set("coor/x", -49970);
        set("coor/y", 20030);
        set("coor/z", 30);
        setup();
        // replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
    object guarder;

    if (objectp(guarder = present("li guanjia", this_object())) &&
        (dir == "east" || dir == "west"))
    {
        return guarder->permit_pass(me, dir);
    }

    return 1;
}
