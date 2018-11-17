// /d/gaoli/yaopu
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "藥鋪");
        set("long", @LONG
走進這裡一股葯香撲面而來，另你精神為之一振。只見藥鋪四壁擺
滿了葯櫃，幾個小夥計正在忙碌的招待着客人。原來這裡的藥材來自五
湖四海，可謂應有盡有，光顧這裡的大多是有錢人與江湖中人。
LONG
        );
set("exits", ([
               "east":__DIR__"xuanwu-2", 
        ]));
       set("objects", ([
                "/d/gaoli/npc/jia" : 1,
                __DIR__"npc/lifuren":1,
        ]));
       setup();
        replace_program(ROOM);
}        
