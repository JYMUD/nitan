// room: /d/xingxiu/tianroad2.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "天山山路");
        set("long", @LONG
這裡是天山東麓，山風從山上吹來，你冷得瑟瑟發抖。路邊是一片
草原。路盡頭松林下一位壯漢正在長嘯練功。北上就是人人害怕的靈鷲
宮了。
LONG );
        set("exits", ([
                "northup"   : "/d/lingjiu/shanjiao",
                "northdown" : __DIR__"xxh",
                "south"     : __DIR__"tianroad1",
        ]));
        set("objects", ([
                CLASS_D("xingxiu")+"/dulong" : 1,
                __DIR__"npc/gushou"  : 1,
                __DIR__"npc/haoshou" : 1,
                __DIR__"npc/boshou"  : 1,
                "/clone/npc/walker" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "xiyu");
        set("coor/x", -50000);
        set("coor/y", 20000);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}