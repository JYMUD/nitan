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
                "west" : __DIR__"xroad2",
                "east" : __DIR__"xiaoximen",
        ]));
	set("coor/x", -16870);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}