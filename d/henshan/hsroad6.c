inherit ROOM;

void create()
{
        set("short", "�ּ���");
        set("long", @LONG
������һ���ּ����������������ѡ��������Ǻ��Ͼ��ڡ�����
�Ǻ�����·���пɹ�·����Ϣ��С��ͤ��
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "west"        : "/d/heizhao/shanlu1",
                "northwest"   : "/d/heizhao/shanlu6",
                "southwest"   : "/d/tiezhang/lx",
                "east"   : __DIR__"chating",
                "north"  : __DIR__"hsroad7",
                "south"  : __DIR__"hsroad5",
        ]));

	set("coor/x", -6930);
	set("coor/y", -5690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}