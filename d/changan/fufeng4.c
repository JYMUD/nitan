//Room: fufeng4.c

inherit ROOM;

void create ()
{
        set ("short", "扶風道");
        set("long", @LONG
扶風道是長安城中心大街，青石板路筆直的伸展出去，一路上行
人比肩，笙歌處處。景物之美，直如神仙境地。
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "north" : "/d/changan/fufeng3",
                "south" : "/d/changan/fufeng5",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10740);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}