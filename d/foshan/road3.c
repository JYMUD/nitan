inherit ROOM;

void create()
{
        set("short", "�ּ��");
        set("long", @LONG
������һ���ּ�С���������������ѡ�����ɽ��ï�ܣ�������棬
����·�˾����˵ض��Ƿǳ���С�ġ�
LONG );
        set("outdoors", "foshan");
        set("objects", ([
                "/d/foshan/npc/bee": 1,
        ]));
        set("exits", ([
                "west"      : __DIR__"road2",
                "northeast" : __DIR__"road4",
        ]));
	set("coor/x", -6650);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}