//1997-3-10 by qyz
#include <room.h>

inherit DOOR_ROOM;



void create()
{
        set("short","莲花台");
        set("long",@LONG
这里是崆峒山的绝顶，孤峰耸峙，独秀霞表，相传为黄帝授道坛，右边就是
万丈深渊，在此登高一呼，众山皆应，放眼四望，崆峒数百里，罗列眼前，如拱
如揖，似碧浪起伏，势皆东倾。当晴霁黎明，观看日出，最为奇观。
LONG);
        set("exits",
        ([
          "south" : __DIR__"lingzhi_yuan",
          "west" : __DIR__"xianren_qiao",
                ]));
        create_door("south",([
                                "name" : "小木门",
                                "lock" : "lock001",
                                "status" : 3,
                                "id"  : ({ "south","小木门","door",}),
                                "other_side_dir" : "north",
                                ]),
                        "north");
        set("outdoors","kongdong");
        setup();
}

void reset()
{
        if( !random( 5) )
        set("objects", ([
                                __DIR__"npc/wuming" : 1,
                ]) );
        ::reset();
}
