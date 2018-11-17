// Room: /d/wuxi/kuaxiqiao.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "跨溪橋");
        set("long", @LONG
跨溪橋俗稱西門弔橋，又稱梁清橋，橋下的梁溪河曾一度成為無錫
的別稱。來自中原及北方的商賈都要從此進出無錫城。而且這也是到無
錫有名的惠山去的路，向西望去，一條大驛道看不到頭，路上來來往往
的人絡繹不絕，向東是西門梁溪門。
LONG );
        set("outdoors", "wuxi");
        set("exits", ([
                "east" : __DIR__"westgate",
                "west" : __DIR__"road14",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1000);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}