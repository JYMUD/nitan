inherit ROOM;

void create()
{
        set("short", "�ּ��");
        set("long", @LONG
������һ���ּ�С���������������ѡ�����ɽ��ï�ܣ�������棬
����·�˾����˵ض��Ƿǳ���С�ġ�
LONG );
        set("outdoors", "foshan");
        set("exits", ([
                "east"      : __DIR__"road6",
                "northwest" : __DIR__"road4",
        ]));
	set("coor/x", -6630);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}