inherit ROOM;

void create()
{
        set("short", "松林");
        set("long", @LONG
這是松林深處，暗無天日，朦朧中只感覺到左右前後到處都是樹
影。地上有一兩個死人骷髏，發著綠熒熒的磷光。你驚駭之間，一腳
踩在鋼針般的松針上！
LONG );
        set("objects", ([
                CLASS_D("wudang") + "/famu" : 1,
        ]));
        set("outdoors", "wudang");
        set("exits", ([
                "north"  : __DIR__"slxl2",
                "south"  : __DIR__"songlin3",
        ]));
        set("coor/x", -340);
        set("coor/y", -190);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}