inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����Ƿ�ɽ������š��ӳ������������н����͵����Ϻ�֮���ˡ�
����һ��������Ĵ���Ƿ�ɽ�����Ҫ�ֵ���
LONG );
        set("outdoors", "foshan");
        set("exits", ([
                "north" : __DIR__"street3",
                "south" : "/d/xiakedao/xkroad3",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -6570);
	set("coor/y", -9760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}