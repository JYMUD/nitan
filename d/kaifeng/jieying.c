inherit ROOM;

void create()
{
        set("short", "�������");
        set("long", @LONG
������������ǿ�����������ֵĵط���˭���뱻������������
���ء����ڹ���������񣬷���ǰ������һյ�����ĵ�������ţ���
�ճ������Ӵ˵��ȥ�����ܿ������������ˡ�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"road6",
                  "east" : __DIR__"tieta",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5050);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}