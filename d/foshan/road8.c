inherit ROOM;

void create()
{
        set("short", "�ּ��");
        set("long", @LONG
������һ���ּ�С���������������ѡ����������������ɽ����
��ͨ�򸣽�Ȫ�ݡ�
LONG );
        set("objects", ([
                __DIR__"npc/zhang": 1,
                __DIR__"npc/zhangkang": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "west" : __DIR__"eastgate",
                "east" : __DIR__"road9",
        ]));
	set("coor/x", -6530);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}