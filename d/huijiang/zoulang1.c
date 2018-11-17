// Room: /d/huijiang/zoulang.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long",@LONG
你走在一條長長的走廊上，四周靜悄悄的，你的腳步聲傳得很遠。
兩旁池塘里的殘荷上停了幾隻呱呱亂叫的青蛙，陣陣輕風吹來，令人慾
醉。
LONG );
        set("outdoors", "huijiang");        
        set("objects", ([
                __DIR__"npc/xinyan" : 1,
        ]));
        set("exits", ([
                "westup" : __DIR__"zoulang2",
                "eastup" : __DIR__"zoulang3",
                "out"    : __DIR__"damen",
        ]));
        set("coor/x", -50060);
        set("coor/y", 9140);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}