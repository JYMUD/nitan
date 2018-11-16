//Room: liande-dadao5.c

inherit ROOM;

void create ()
{
        set ("short", "连德大道");
        set("long", @LONG
城内街道，与南北三条并行的大街，和东西的二条主街互相交错
而成。五条大街在这清朗的夜初，却见人来车往，灯火通明，别有一
番热闹。其他小街横巷，则依这些主街交错布置，井然有序。
LONG );
        set("exits",([//sizeof() == 3
                "south" : "/d/changan/liande-nankou",
                "north" : "/d/changan/liande-dadao4",
                "east" : "/d/changan/xiaojia-qianyuan",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10680);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
        