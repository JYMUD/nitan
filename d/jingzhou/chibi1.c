inherit ROOM;

void create()
{
        set("short",  "小路" );
        set("long", @LONG
这是一条通向江边的小路，路十分的陡，走起来得小心一点，四
周静悄悄的，只闻的鸟儿歌唱的声音。
LONG );
        set("outdoors", "jingzhou");

        set("exits", ([
                "northup" : __DIR__"qingshan",
                "southdown" : __DIR__"chibi2",
        ]));
        set("coor/x", -350);
        set("coor/y", -200);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
} 