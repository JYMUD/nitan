// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "�鷿");
        set ("long", @LONG
��������ү�ӵ��鷿����������ࡣ����һ�°�ǽ�ر����ۡ�
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "south" : __DIR__"wan_xilou",
        ]));

        set("no_clean_up", 0);
        set("coor/x", -7120);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}