// Room: /d/yanziwu/path6.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "碎石小径");
        set("long", @LONG
一条小路通往花圃深处。走在小路上，可以听到近处清溪水响。地
上碎石铺得很是齐整，看来是花了不少功夫了。南边就是蔓陀山庄的花
圃了，满庄满园的花，都是那边栽培出来的。北面通向红霞楼，东面是
花肥房。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"huapu2",
                "north"  : __DIR__"path7",
                "east"   : __DIR__"shiwu",
                "west"   : __DIR__"path5",
        ]));
        set("coor/x", 1250);
        set("coor/y", -1270);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}