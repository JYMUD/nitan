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
                "southwest" : __DIR__"boshulin7",
                "south" : __DIR__"boshulin7",
                "east" : __DIR__"boshulin7",
                "southeast" : __DIR__"boshulin7",
                "west" : __DIR__"boshulin6",
                "northwest" : __DIR__"boshulin8",
                "north" : __DIR__"boshulin7",
                "northeast" : __DIR__"boshulin7",
        ]));

        set("coor/x", -10630);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

