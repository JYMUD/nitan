// /guanwai/longmen.c

inherit ROOM;

void create()
{
        set("short", "龍門峰");
        set("long", @LONG
龍門峰在乘槎河西岸，因狀如門形，故名龍門。崇崖峻壁，形態奇特，
宛如卧龍吸水，傳說大禹治水曾到此峰，旁有蝌蚪形石柱。
LONG );
        set("exits", ([
                "northeast" : __DIR__"damen",
                "west"      : __DIR__"luming",
                "east"      : __DIR__"tianhuo",
                "southdown" : __DIR__"tianchi1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "changbai");
        setup();
        replace_program(ROOM);
}