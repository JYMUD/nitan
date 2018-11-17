// Room: /d/guiyun/caodi3.c
// Last Modified by winder on Jun. 29 2001

inherit ROOM;

void create()
{
        set("short", "草地");
        set("long",@LONG
一片青翠的草地。綠草如蔭，茂密地生長着，草叢間有一些不知名
的小蟲在鑽來鑽去。遠處有一片樹林。
LONG
);
        set("exits",([
                "west"  : __DIR__"caodi1",
                "north" : __DIR__"shulin3",
        ]) );
        set("no_clean_up",0);
        set("outdoors", "guiyun");
        set("coor/x", 300);
        set("coor/y", -830);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
