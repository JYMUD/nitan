inherit ROOM;

void create()
{
        set("short", "�ٵ�");
        set("long", @LONG
����һ�����ϵĻ����ٵ���������һƬƬ�����͵�ˮ���
���е���ͯ������������������������������˶�����������
��ͷ�󺹵ĴҴҸ�·���ƺ���������������������԰��⡣
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "east" : __DIR__"xroad1",
                "west" : "/d/dali/road1",
        ]));
	set("coor/x", -16880);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}