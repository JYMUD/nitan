// Room: /d/henshan/hsroad2.c 黃土路
// Modified by Java on Feb.14 1998

inherit ROOM;

void create()
{
        set("short", "黃土路");
        set("long", @LONG
你走在一條塵土飛揚的黃土路上，兩旁是陰森森的樹林。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "north" : __DIR__"hsroad1",
                "southwest" : __DIR__"hsroad3",
                "southeast" : "/d/yanping/gudao1",
                "northeast" : "/d/huangshan/shanmen",
        ]));

        set("no_clean_up", 0);
	set("coor/x", -6860);
	set("coor/y", -5690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}