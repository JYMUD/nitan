inherit ROOM;

void create()
{
        set("short", "�ּ���");
        set("long", @LONG
������һ���ּ����������������ѡ��������Ǻ������ڡ��ϱ�
�Ǳ���ϡ�
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "north"  : __DIR__"hsroad8",
                "south"  : __DIR__"hsroad6",
        ]));
        set("objects", ([
                "/clone/quarry/gou" : 1,
        ]));

	set("coor/x", -6930);
	set("coor/y", -5680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}