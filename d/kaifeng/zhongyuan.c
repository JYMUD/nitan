inherit ROOM;

void create()
{
        set("short", "��Ժ");
        set("long", @LONG
��Ժ��Ϊǰ�������֣�Ժ�ӵ������������Ƹ��������߲㡣���
�������ơ�ǰ�߲��ֳ��м���е��⣬�����ǻ��ԣ�����һ�øߴ��
�����������������ʯ��ͨ����۱���ϱ����������������ի
����������ԡ�ҡ�
LONG );
        set("objects", ([
                  __DIR__"npc/obj/tiefutu" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"tianwang",
                  "north" : __DIR__"daxiong",
                  "east" : __DIR__"chufang",
                  "west" : __DIR__"yushi",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5040);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}