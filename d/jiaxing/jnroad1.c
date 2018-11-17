// Room: /d/jiaxing/jnroad1.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在江南的一條山路上，到處鶯飛草長。時值春日，路旁的山坡
上開滿了金黃色的油菜花。
LONG );
        set("exits", ([
                "northwest" : "/d/taishan/yidao1",
                "south"     : __DIR__"jnroad2",
        ]));
        set("outdoors", "jiangnan");
        set("no_clean_up", 0);
	set("coor/x", 1180);
	set("coor/y", -1760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}