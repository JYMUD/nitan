inherit ROOM;

void create()
{
        set("short", "��ɽͤ");
        set("long", @LONG
���ڵ��˰�ɽͤ�������뵽ף�ڷ����۸̻߳����г̣���ǡ����
һ��֮����·��Сͤ��Ȼ�Ѽ��žã�����Ϊ���������ڷ���ꡣ
LONG );

        set("exits", ([
               "southdown"  : __DIR__"shanlu4",
               "northwest"    : __DIR__"shanlu002",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "henshan");

	set("coor/x", -6910);
	set("coor/y", -5550);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}