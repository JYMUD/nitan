// /guanwai/huandi1.c

inherit ROOM;

void create()
{
        set("short", "��·");
        set("long", @LONG
���ǳǶ���һ����·��·�����ҵĳ�����ϥ�ĻĲݣ�Զ������һ�ˡ���
�Ըɿݵ������������˳�Ⱥ����ѻ���������������ڻ�Ұ��ԶԶ��ȥ��һ��
�����ľ���
LONG );
        set("exits", ([
                "southwest" : __DIR__"dongcheng",
                "northeast" : __DIR__"huandi2",
        ]));
        set("objects", ([
                CLASS_D("murong") + "/longcheng" : 1,
        ]));
        set("outdoors", "guanwai");
        set("coor/x", 4010);
	set("coor/y", 9250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}