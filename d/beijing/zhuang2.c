inherit ROOM;

void create()
{
        set("short", "С·");
        set("long", @LONG
������һ��С·�ϡ�ǰ���·��᫣����˺��١�ǰ����Լ�з���
�ɼ���
LONG );
        set("exits", ([
                "south" : "/d/beijing/zhuang1",
                "north" : "/d/beijing/zhuang3",
        ]));
        set("objects", ([
                "/d/wudang/npc/tufei1" : 1,
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2780);
	set("coor/y", 7630);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}