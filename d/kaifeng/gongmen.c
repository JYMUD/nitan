inherit ROOM;

void create()
{
        set("short", "ʯ����");
        set("long", @LONG
��ʯͷ��������һ�����ţ���Խ���ɣ������ο����ơ�������˩
���ʯ��������ǰ��һ��ĵط����п����ʯ������������޴��ʯ
ͷ��һ���񵽵��£��ںͿڵĵط����и���׿��Բ���ˡ�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "southup" : __DIR__"8bao",
                  "northdown" : __DIR__"road",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5040);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}