inherit ROOM;

void create()
{
        set("short", "Сɽ��");
        set("long", @LONG
������һ��Сɽ�����������˹��˸ߵĳ��ݣ�������һ���ҷظڣ�
��˵�����ֹ�����û�˸�ȥ��һ�����������ŵ��������ë����
LONG );
        set("exits", ([
                "southdown" : __DIR__"houmen",
                "eastdown" :__DIR__"luan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -7120);
	set("coor/y", -2010);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}