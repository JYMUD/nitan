// xiuxis.c 休息室


inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這是一間石洞，洞內中間擺着幾張大床，幾張桌子，看來是
個休息的地方，室中光線柔和，使人更增睡意。
LONG );
        set("exits", ([
                "east" : __DIR__"yingbin",
        ]));
        set("no_fight",1);
        set("no_steal",1);
        set("sleep_room",1);
        set("no_clean_up", 0);
        set("coor/x", -3090);
        set("coor/y", -22080);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}