inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
������һ����ʯ������ʯ�ף���������ͨ��������Ժ����������
һƬ���̵����֡�
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "southdown" : __DIR__"zizhulin",
                "north" : __DIR__"shuyuan1",
        ]));
        set("coor/x", -7090);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}