// Room: /d/huanggong/yangxin2.c

inherit ROOM;

void create()
{
        set("short", "���Ե�");
        set("long", @LONG
������λ��, ����̫�ϻʾ;�ס�ڴ�. ̫�ϻʲ������ʳ���, ����
����Ϣ, ��������. ֱ����������.
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "north" : __DIR__"leshou",
                "east"  : __DIR__"changyinge",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2810);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}