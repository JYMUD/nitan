inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
������һ����ʯ�̳ɵĴ���ϡ����ܵ���Ұ�Ѿ�����ѩ���ǣ�������ȥ
�����Լ��Ѿ��������ޱ��޼ʵ�ѩԭ�С���������ѩ����Х������������
�����������������ƺ���һ�ƴ�������
LONG );
        set("exits", ([
                "north" : __DIR__"muqiao",
                "south" : __DIR__"road7",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "guanwai");
        set("coor/x", 3990);
	set("coor/y", 9210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}