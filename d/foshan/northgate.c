inherit ROOM;

void create()
{
        set("short","����");
        set("long", @LONG
�����Ƿ�ɽ��ı��š����������򱱣���������ɴ���ԭ������
һ��������Ĵ���Ƿ�ɽ�����Ҫ�ֵ���
LONG );
        set("outdoors", "foshan");
        set("exits", ([
                "south" : __DIR__"street3",
                "north" : __DIR__"nanling",
        ]));
	set("coor/x", -6570);
	set("coor/y", -9740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}