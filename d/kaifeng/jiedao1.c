inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����������ϱ������������ţ�������ӯ�ţ�����ǰ���ϳ�Ѳʱ
���ߵĵ��������޵��Ǹ���ƽ���������ߵ��̲��ϡ�������ǿ��⸮
�Ĵ��ã�������һ��Ϳ��Գ����ˡ�
LONG );
        set("outdoors", "kaifeng");
        set("exits", ([
                  "west" : __DIR__"kaifeng",
                  "north" : __DIR__"jiedao",
                  "south" : __DIR__"jiedao2",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -5040);
	set("coor/y", 2150);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}