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
            "east" : "d/xiangyang/caodi6",
            "southwest" : __DIR__"hunanroad2",
        ]));

        set("coor/x", -3590);
        set("coor/y", -160);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}