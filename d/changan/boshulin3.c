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
                "southwest" : __DIR__"boshulin3",
                "south" : __DIR__"boshulin2",
                "east" : __DIR__"boshulin3",
                "southeast" : __DIR__"boshulin3",
                "west" : __DIR__"boshulin4",
                "northwest" : __DIR__"boshulin3",
                "north" : __DIR__"boshulin3",
                "northeast" : __DIR__"boshulin3",
        ]));

        set("coor/x", -10640);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

