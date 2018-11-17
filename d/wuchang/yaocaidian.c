//Edited by fandog, 02/15/2000

inherit ROOM;
void create()
{
        set("short", "藥材店");
        set("long", @LONG
這是一家藥材店，走進來便聞到刺鼻的藥味兒。葯柜上幾百個小抽
屜分門別類地寫着藥名和價格。藥店掌柜坐在茶几旁，獨自喝着茶，看
也不看你一眼。一名小夥計站在櫃檯後招呼着顧客。櫃檯上貼着一張發
黃的廣告(guanggao)。
LONG );
        set("item_desc", ([
                "guanggao" : "本店出售以下藥品：
當歸  靈芝  田七  紅參  金釵\n"
        ]));
        set("objects", ([
                __DIR__"npc/boss1" : 1,
                __DIR__"npc/huoji1" : 1,
        ]));
        set("exits", ([
                "south" : __DIR__"hzjie4",
        ]));
	set("coor/x", -5100);
	set("coor/y", -1870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}