// Room: /d/huanggong/gong5.c

inherit ROOM;

void create()
{
        set("short", "太極殿");
        set("long", @LONG
這裡已是深宮內院. 陳列着一些工藝美術, 這就是后妃嬪女居住的
地方. 進了這兒可以深深感受到何謂“一入宮門深似海”.
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "east"  : __DIR__"tinglang3",
                "north" : __DIR__"gong3",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2840);
	set("coor/y", 7761);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}