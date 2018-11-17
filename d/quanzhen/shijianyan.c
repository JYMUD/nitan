// shijianyan.c 試劍岩
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "試劍岩");
        set("long", @LONG
石階旁立着一塊大岩石，上面斑斑駁駁的儘是砍傷。這塊大岩
石便是全真教的試劍岩，天下的英雄來到這裡，望着先輩們練劍時
在岩石上的砍痕，無不肅然起敬。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "northdown" : __DIR__"shijie4",
                "southup" : __DIR__"shijie8",
                "east" : __DIR__"jiaobei",
        ]));
        set("objects",([
                CLASS_D("quanzhen")+"/yin" : 1,
                __DIR__"npc/daotong" : 2,
        ]));

        set("coor/x", -3150);
        set("coor/y", 110);
        set("coor/z", 160);
        setup();
        replace_program(ROOM);
}