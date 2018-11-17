// pine_forest9.c 松林
// Last Modified by winder on Aug. 18 2002

inherit ROOM;


void create()
{
        set("short", "松林");
        set("long", @LONG
這是松林深處，暗無天日，朦朧中只感覺到左右前後到處都是樹影。
地上有一兩個死人骷髏，發著綠熒熒的磷光。你驚駭之間，一腳踩在鋼
針般的松針上！
LONG
        );
        
        switch(random(11)){
        case 1:
                set("objects", ([ __DIR__"obj/songguo" : 2]));
                break;
        case 2:
                set("objects", ([ __DIR__"npc/snake" : 1]));
                break;
        case 9:
                set("objects", ([
                        __DIR__"obj/songguo" : 1,
                        __DIR__"npc/snake" : 1]));
                break;
        case 12:
                set("objects", ([ __DIR__"npc/snake" : 2]));
                break;
        case 10:
                set("objects", ([ __DIR__"obj/pine" : 1]));
                break;
        }                          

        set("exits", ([
                "south" : __DIR__"pine_forest"+(random(11)),
                "north" : __DIR__"pine_forest10",
                "east" : __DIR__"pine_forest"+(random(9)),
                "west" : __DIR__"pine_forest"+(random(9)),
        ]));
        set("outdoors", "wudang");
        setup();
}


void init()
{
        object me = this_player();
        
        if( !objectp(query_temp("armor/boots", me)) )
                me->receive_damage("qi", 10, "被松針扎死了");  

}
