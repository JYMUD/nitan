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
                "north" : __DIR__"htroad2",
                "southwest" : "/d/dali/heisenlin",
        ]));
	set("coor/x", -16840);
	set("coor/y", -7270);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}