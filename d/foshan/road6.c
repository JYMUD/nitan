inherit ROOM;

void create()
{
        set("short", "�ּ��");
        set("long", @LONG
������һ���ּ�С���������������ѡ�����ɽ��ï�ܣ�������棬
����·�˾����˵ض��Ƿǳ���С�ġ�
LONG );
        set("objects", ([
                __DIR__"obj/shikuai": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "west" : __DIR__"road5",
                "east" : __DIR__"road7",
        ]));
        set("objects", ([
                __DIR__"npc/youming" :  1,
        ]));
	set("coor/x", -6620);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}