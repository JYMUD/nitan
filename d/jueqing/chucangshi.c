inherit ROOM;

void create()
{
        set("short", "儲藏室");
        set("long", @LONG
這裡是絕情谷的儲藏室，裡面堆放着一些雜物。
LONG);
        set("exits", ([
               "west"   : __DIR__"houtang",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
