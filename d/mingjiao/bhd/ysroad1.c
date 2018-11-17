// ysroad1.c 岩石路
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIR"岩石路"NOR);
        set("long", @LONG
這是一岩石路，由此去火山尚須四十多里路。但在此已可以看到
四面山上一縷黑煙衝天而起。岩石路皆由火山灰堆成，厲時久，地面
十分堅硬。
LONG );
	set("exits",([
		"east" : __DIR__"shishan",
		"west" : __DIR__"ysroad2",
	]));
	set("outdoors","冰火島");
	setup();
}
