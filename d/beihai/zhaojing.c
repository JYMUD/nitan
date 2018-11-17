// /d/beihai/zhaojing.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "昭景門");
        set("long", @LONG
團城為一高台，圓形，台高丈五，周長八十二丈。城之兩掖有門，
東曰昭景，西曰衍祥，入門有蹬道。這裡就是團城的昭景門。門口有幾
個人在掃地。
LONG
        );
        set("exits", ([
                "west"      : __DIR__"chengguang",
                "north"     : __DIR__"yonganqiao",
                "northeast" : __DIR__"qianmen",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -190);
        set("coor/y", 4060);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}