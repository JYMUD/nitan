// Room: /city/biaojudy.c

inherit ROOM;

void create()
{
        set("short", "��Ժ");
        set("long", @LONG
��Ժ���Ե���Щ���ң������ֺ���ʦ�ǽ����������ƺ�����������
æµ��ʲô��һ�úܴ����������Ժ�����룬���������ĸ��ݴ���һ��
��ˬ��
LONG );
        set("exits", ([
                "out"   : __DIR__"biaoju",
                "north" : __DIR__"biaojuzt",
                "east"  : __DIR__"biaojuhc",
                "west"  : __DIR__"biaojucyf",
        ]));
        set("objects", ([
                __DIR__"npc/shi" : 1,
        ]));
        set("outdoors", "fuzhou");
	set("coor/x", -101);
	set("coor/y", -6171);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}