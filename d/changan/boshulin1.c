// This program is a part of NT MudLIB

inherit ROOM;
void create()
{
        set("short", "������");
        set("long",@LONG
������һƬ֦��Ҷï�İ����֣����ݳ��ñ�ض��ǣ�������ԭʼ
�����֣����ƺ���ʧ�˷���
LONG
        );
        set("outdoors", "changan");
        set("exits", ([
                "northeast" :__DIR__"boshulin2",
                "southeast" :__DIR__"boshulin1",
                "east" :__DIR__"boshulin1",
                "north" :__DIR__"boshulin1",
                "west" :__DIR__"boshulin1",
                "northwest" :__DIR__"boshulin1",
                "southwest" :__DIR__"boshulin1",
                "south" :__DIR__"road4",
        ]));
        set("coor/x", -10650);
	set("coor/y", 1940);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

