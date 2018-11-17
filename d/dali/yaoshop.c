//Room: /d/dali/yaopu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","藥鋪");
        set("long", @LONG
這是一家神秘的藥鋪，座落在大和街和市中心的交界處，普通的
門面和招牌，街坊們都說這家藥鋪的葯靈驗的很。從葯柜上的幾百個
小抽屜里散發出來的一股濃濃的藥味，讓你幾欲窒息。據說這家店鋪
有一種很神密的藥物。
LONG );
        set("objects", ([
           "/d/dali/npc/hehongyao": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/taiheeast",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}