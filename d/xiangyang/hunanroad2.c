// /d/xiangyang/hunanroad2.c

inherit ROOM;

void create()
{
        set("short", "��·");
        set("long", @LONG
����������������·�ϣ�ż��������������ҴҶ�����������
���Ǻ��ϵؽ磬��������������ڡ�
LONG );
        set("outdoors", "tiezhang");

        set("exits", ([
                "northeast" : __DIR__"hunanroad1",
                "south" : __DIR__"lx",
        ]));

        set("coor/x", -3600);
        set("coor/y", -170);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}