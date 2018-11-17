inherit ROOM;

void create()
{
        set("short", "舍利塔");
        set("long", @LONG
這是天龍三塔之一，建於唐初，年代久遠。傳說月圓之夜，在此
塔之下默許心愿，塔頂會出現聖光指點迷津，助你達成心愿。
LONG );
        set("outdoors", "tianlongsi");
        set("exits", ([
                "west" : __DIR__"talin",
        ]));
        set("objects",([
                "/d/wudang/npc/guest" : 2,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}