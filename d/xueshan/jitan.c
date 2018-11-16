//  jitan.c 祭坛

inherit ROOM;

void create()
{
        set("short","祭坛");
        set("long", @LONG
 这里是雪山寺祭坛，中间一个高台，青石砌就。周围摆满了木柴
和酥油，旁边一个盛水的颅钵摆着一只法铃。一些痛苦和可怜的亡灵
可以在这里获得超度。
LONG );
        set("outdoors","xueshan");
        set("no_fight","1");
        set("exits",([
                "north" : "/d/xueshan/chang",
        ]));
        set("objects",([
                "/d/xueshan/npc/x_lama": 2,
//                "/d/xueshan/npc/fsgelun": 2,
//                "/d/xueshan/obj/jitan2": 1,
//                "/d/xueshan/obj/faling": 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

/*
int valid_leave(object me, string dir)
{
        object ob;
        ob=(present("fa tan", (environment(me))));
        if (! objectp(ob)) return ::valid_leave(me, dir);
        if( query("name", me) == query("pending", ob )
         && query("burning", ob) )
                return notify_fail("你法事没做完就想走？\n");
        return ::valid_leave(me, dir);
}
*/