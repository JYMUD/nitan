// Room: /city/biaojuxf1.c

inherit ROOM;

void create()
{
        set("short", "���᷿");
        set("long", @LONG
�����ﲼ�úܼ򵥣�ֻ��һ��С����һ��С�����ͼ��ŷ��ʡ���̨
�Ϸ���һ���ű���������ż�֦����С���������䲻�󣬵��Ǹ�������
���ʵĸо���
LONG
        );
        set("exits", ([
                "east" : __DIR__"biaojuhy",
        ]));
        set("objects", ([
                __DIR__"npc/fu" : 1,
        ]));
	set("coor/x", -111);
	set("coor/y", -6151);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}