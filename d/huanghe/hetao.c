// Room: /huanghe/hetao.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "河套");
        set("long", @LONG
常言到“黃河九害，富了一套”。河套地區灌溉系統發達，土地肥
沃，是種莊稼的好地方。
LONG );
        set("exits", ([
                "southwest" : __DIR__"huangtu",
                "east"      : __DIR__"huanghe_1",
                "west"      : "/d/yongdeng/qingcheng",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", -2000);
        set("coor/y", 800);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}