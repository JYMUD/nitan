inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
��ɽ��ֵ�ƽ���������������ţ�������һ��������������ΰ��
�ô�һ��������
LONG );
        set("objects", ([
                __DIR__"npc/jiading": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "north" : __DIR__"beidimiao",
                "west"  : __DIR__"westgate",
                "east"  : __DIR__"street2",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -6590);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}