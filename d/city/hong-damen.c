//Room: /d/ruzhou/hong-damen.c
// by llm 99/06/12

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "紅娘庄大門");
   set("long",
"眼前是一座氣勢雄偉的大庄庭，門廊高大、朱牆黃瓦，竟有些與皇宮\n"
"相似的味道，只是大門兩邊立的不是麒麟、獅獸，而是笑眯眯的喜財童子\n"
"童女，而且大門敞開，任人隨意進入，正中上面一塊巨大的烏木匾牌\n"
HIR"            紅    娘    庄\n"NOR
"\n");
        set("exits", ([
                "west" : __DIR__"beimen",
                "east" : __DIR__"hong-zoulang",
   ]) );


   set("objects", ([
//           __DIR__"npc/meipo" : 1,
      ]) );
	set("coor/x", 10);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
   replace_program(ROOM);
}