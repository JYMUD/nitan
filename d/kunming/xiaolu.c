inherit ROOM;

void create()
{
        set("short", "С·");
        set("long", @LONG
������һ��С·����Ϊ��ƽ������������һЩ��ʯ������
��״��������Ȥ ��
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "north" : __DIR__"yunnan4", 
                "south"  :__DIR__"shilin",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy3" : 1,
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -16770);
	set("coor/y", -7190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}