inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
��������ϱ��Ľֵ��ǻ��ϳ�Ѳʱ��Ҫ��������������������ӯ
�ţ����ߵ��̲��ϡ��ֵ������������ĵ���ӡ�
LONG );
        set("no_clean_up", 0);
        set("outdoors", "kaifeng");
        set("exits", ([
                  "north" : __DIR__"road3",
                  "west" : __DIR__"gongyuan3",
                  "south" : __DIR__"zhuque",
                  "east" : __DIR__"daoxiang",
        ]));

	set("coor/x", -5050);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}