// Room: /d/huanggong/ningshougong.c

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
���������ٹ��Ĵ���. ������ȥ����̫�ϻ��������ٹ���.
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                 "north"      : __DIR__"huangjidian",
                 "south"      : __DIR__"huangjimen",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2790);
	set("coor/y", 7751);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}