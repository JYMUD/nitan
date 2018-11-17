// regiser: roome.c
// by Doing

inherit ROOM;

void create()
{
        set("short", "桃源瓦房");
        set("long", @LONG
這裡是一間小瓦房，布置的非常舒適，一小鬼舒舒服服的靠在椅子
上，輕搖羽扇，有如關羽之長，宛若諸葛之亮。正笑吟吟的看着你進來。
LONG );
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/wei" : 1,
        ]));
        set("exits", ([
                "north"  : __DIR__"entry",
                "out"   : __DIR__"yanluodian",
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (! objectp(ob = present("wei xiaobao", this_object())))
        {
                ob = new(__DIR__"npc/wei");
                ob->move(this_object());
        }

        ob->check_leave(me, dir);
        return ::valid_leave(me, dir);
}