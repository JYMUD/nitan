inherit ROOM;

void create()
{
        set("short", "�ּ��");
        set("long", @LONG
������һ���ּ�С���������������ѡ�����������һ������·��
����ĵ�·Ҫ��һЩ��
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "northwest" : "/d/yueyang/nanmen",
                "south"     : __DIR__"hsroad7",
        ]));

	set("coor/x", -6930);
	set("coor/y", -5670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}