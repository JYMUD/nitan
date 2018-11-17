//nzlangn2.c                四川唐門―青石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青石小路");
        set("long",
"這是一條青石鋪就的小路。由於來來往往的人數太多，粗糙的青石已\n"
"經被磨的光滑如鏡。一些唐門的弟子往來穿梭，這裡還真是很熱鬧。這裡向\n"
);
        set("exits", ([
                        "south" : __DIR__"nzlangn1",
                        "north" : __DIR__"nzlangn3",
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}