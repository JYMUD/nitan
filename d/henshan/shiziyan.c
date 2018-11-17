inherit ROOM;

void create()
{
        set("short", "獅子岩");
        set("long", @LONG
獅子岩布滿奇形怪狀的岩石，細究則絕類獅子，騰躍伏吼，各肖
其類。到獅子岩，祝融峰已經在望了。
LONG );
        set("exits", ([ 
               "southwest"  : __DIR__"nantian",
               "northup"    : __DIR__"wangritai",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6930);
	set("coor/y", -5510);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}