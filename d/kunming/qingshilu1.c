inherit ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
һ����ʯ�������ʯ�̳ɣ�ƽ̹������ԶԶ�Ŀ��Կ�����
���ˡ�
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "west" : __DIR__"qingshilu2", 
                "east"  :__DIR__"qingshilu",
        ]));
        set("objects", ([
                "/d/beijing/npc/tangzi" : 1,
        ]));
	set("coor/x", -16800);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}