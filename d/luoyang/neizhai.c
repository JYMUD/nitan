// Room: /u/a/agah/neizhai.c

inherit ROOM;

void create()
{
        set("short", "內宅");
        set("long", @LONG
這裡是衙門的內宅，住着知府的家眷。只見宅內布置的富麗堂皇，珠
光寶氣，名貴的傢具，精緻的擺設，大理石鋪成的地面映的滿堂生輝。不
過外人是不能隨便進出的。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"yamen",
]));

	set("coor/x", -6960);
	set("coor/y", 2200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}