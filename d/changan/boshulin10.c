// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����ǰ��Ȼ���ʣ������߳�����Ƭ�����֣�����������һƬ�Ӳ�
�����Ĳݵء�
LONG
        );
        set("outdoors", "changan");
        set("exits", ([ /* sizeof() == 3 */
                "south" : __DIR__"boshulin9",
                "east" : __DIR__"caodi",
        ]));

        set("coor/x", -10630);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

