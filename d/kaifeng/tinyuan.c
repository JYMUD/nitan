inherit ROOM;

void create()
{
        set("short", "��ͤ԰");
        set("long", @LONG
������һƬ��ľ������԰�֡�԰�ֵ��ϱ����߷ֱ�����Һ�����
�Һ������б̲����������ߴ����������������𡣴Ӵ�������ͤ��
�����������ֵ���
LONG );
        set("objects", ([
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"longting",
                "west" : __DIR__"wroad3",
        ]));
        set("objects", ([
                CLASS_D("lingxiao") + "/shiqing" : 1,
        ]));

        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}