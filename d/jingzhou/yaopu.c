inherit ROOM;

void create()
{
        set("short", "藥鋪");
        set("long", @LONG
這裡是一家藥鋪，一股濃濃的藥味讓你幾欲窒息，那是從葯柜上
的幾百個小抽屜里散發出來的。神醫華陀二世坐在茶几旁，獨自喝着
茶，看也不看你一眼。一名小夥計站在櫃檯後招呼着顧客。
LONG );
        set("objects", ([
                __DIR__"npc/huatuo" : 1,
                __DIR__"npc/huoji" : 1,
        ]));
        set("exits", ([
                "east" : __DIR__"beidajie2",
        ]));

        set("coor/x", -7110);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}