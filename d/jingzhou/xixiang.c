inherit ROOM;

void create()
{
        set("short", "Ѿ���Է�");
        set("long", @LONG
����Ѿ�ߵķ��䡣���г���򵥣�ûʲô������
LONG );

        set("exits", ([
                "east" : __DIR__"houyuan",
        ]));
        set("objects", ([
                __DIR__"npc/juyou" : 1,
        ]));
        set("cost", 0);
        set("coor/x", -7120);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}