// Room: /d/northft/ftn8.c

inherit ROOM;

void create()
{
	set("short", "山路");
	set("long", @LONG
这是一条窄窄的上山小路，两旁怪石嶙峋，中间的路倒是很
平坦，看样子是被人专门开掘出来的。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "eastup" : __DIR__"ftn9",
  "westdown" : __DIR__"ftn7",
]));

	set("outdoors", "northft");
	setup();
	replace_program(ROOM);
}
