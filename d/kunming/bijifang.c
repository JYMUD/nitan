inherit ROOM;

void create()
{
        set("short",  "�̼���" );
        set("long", @LONG
������ʤ֮һ���̼��ʣ���˵��ÿ���һ�죬��Ӱ�Ӻͽ�
���ʵ�Ӱ�ӽ����ӡ����Ϊ��̽��ԣ�ΡΡ��ۡ�
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "west" : __DIR__"jinrilou", 
                "east"  :__DIR__"dongmen",
        ]));
        set("objects", ([
                "/d/beijing/npc/jumin1" : 1,
        ]));
	set("coor/x", -16830);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}