inherit ROOM;

void create()
{
        set("short", "�ּ��");
        set("long", @LONG
������һ���ּ�С���������������ѡ�����ɽ��ï�ܣ�������棬
����·�˾����˵ض��Ƿǳ���С�ġ�
LONG );
        set("objects", ([
                __DIR__"obj/hua1": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "west"  : __DIR__"road1",
                "east"  : __DIR__"road3",
        ]));
	set("coor/x", -6660);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}