inherit ROOM;

void create()
{
        set("short", "���ݳ�");
        set("long", @LONG
���ݳ��Ǳ����Ĵ�ǣ������Ǳ��ұ���֮�ء��������ڴ�פ����
�����̲��������������ˣ����������𸽽�ɽ�ϵĲݿܡ�����������
ȥ��ɽ�ıؾ�֮�����ٱ��̲�Ҳʮ���ϸ񡣴������򶫳����ţ�����
������֮�е���ɽ�ˡ�
LONG
        );

        set("exits", ([
                "south" : __DIR__"nandajie",
                "west"  : __DIR__"xidajie",
                "east"  : __DIR__"dongdajie",
                "north" : __DIR__"beidajie",
        ]));

        set("objects", ([
                "/clone/npc/xunbu" : 1,
                "/clone/npc/walker"  : 1,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
