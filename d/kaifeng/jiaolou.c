inherit ROOM;

void create()
{
        set("short", "����¥");
        set("long", @LONG
��¥�ǽ��ڳ�ǽ֮�ϣ����ڱ��������Ĵ�����ֻ��¥�Ķ��˹���
һյ�������Ӵ�Զ����Զ��ɽˮ̨ͤ��һһ��Ŀ��������ȥ��������
�֡����������˲��ϡ�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "eastdown" : __DIR__"zhuque",
                  "westdown" : __DIR__"wroad2",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2240);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}