// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������һƬ֦��Ҷï�İ����֣����ݳ��ñ�ض��ǣ�������ԭʼ
�����֣����ƺ���ʧ�˷���
LONG
        );
        set("outdoors", "changan");
        set("exits", ([ /* sizeof() == 8 */
                "southwest" : __DIR__"boshulin8",
                "south" : __DIR__"boshulin9",
                "east" : __DIR__"boshulin9",
                "southeast" : __DIR__"boshulin9",
                "west" : __DIR__"boshulin9",
                "northwest" : __DIR__"boshulin9",
                "north" : __DIR__"boshulin10",
                "northeast" : __DIR__"boshulin9",
        ]));

        set("coor/x", -10630);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

