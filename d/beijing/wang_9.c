inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
这里就是京城最为著名的王府井大街。你走在这条繁忙的街道上，
街道上车水马龙，人来人往，热闹非凡。南边接京城的交通要道东长
安街，西边是繁华的地安门东大街广场。北方穿过地东大街可以到达
文庙。
LONG );
       set("exits", ([
                "north" : "/d/beijing/dong_3",
                "south" : "/d/beijing/wang_7",
                "east" : "/d/beijing/wang_10",
                "west" : "/d/beijing/di_donggc",
        ]));

        set("objects", ([
                "/d/beijing/npc/haoke1" : 1,
        ]));

	set("coor/x", -2780);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}