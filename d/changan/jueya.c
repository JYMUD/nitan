// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
    set("short", "����");
    set("long",@LONG
��ǰһƬ�տ���������һ������׵����£���һ�������±ߵ�
���Ҿͷ׷�������ȥ���þö�û����������
LONG
        );
        set("outdoors","changan");
        set("exits", ([
                "west" :__DIR__"caodi",
        ]));
        set("coor/x", -10610);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}


