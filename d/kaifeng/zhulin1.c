inherit ROOM;

void create()
{
        set("short", "Сé��");
        set("long", @LONG
���߽������е�Сé�ݣ�������һ�£���é�ݽ�����é�ݸ�����
�ıߵ�ǽ������һ������ë�������¶��ɵģ����е�����Ҳ���Ǵ�
�����ƣ����ϷŵĲ���������������ɵġ�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out" : __DIR__"zhulin",
        ]));

	set("coor/x", -5021);
	set("coor/y", 2139);
	set("coor/z", 9);
	setup();
        replace_program(ROOM);
}