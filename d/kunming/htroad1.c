inherit ROOM;

void create()
{
        set("short", "����·");
        set("long", @LONG
����һ�����ϵĻ��������������һƬƬ�����͵�ˮ���
���е���ͯ������������������������������˶�����������
��ͷ�󺹵ĴҴҸ�·���ƺ���������������������԰��⡣
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "south" : __DIR__"htroad2",
                "north" : __DIR__"nanmen",
        ]));
	set("coor/x", -16840);
	set("coor/y", -7250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}