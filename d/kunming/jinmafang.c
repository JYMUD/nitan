inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������ʤ֮һ�������ʣ���˵��ÿ���һ�죬��Ӱ�Ӻͱ�
���ʵ�Ӱ�ӽ����ӡ����Ϊ��̽��ԣ�ΡΡ��ۡ�
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "west" : __DIR__"xiaoximen",
                "east"  :__DIR__"jinrilou",
        ]));

        set("objects", ([
                "/d/beijing/npc/old1" : 1,
                "/d/beijing/npc/boy1" : 1,
        ]));
	set("coor/x", -16850);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}