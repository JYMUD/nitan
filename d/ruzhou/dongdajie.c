inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
���������ݳǵĶ���֣��ֵı�����һ�Ҵ����̣���ȥ�����ݳ���
�ģ�������ȥ����ɽ�Ķ��ţ�����Ҳû��ʲô���̡�
LONG
        );

        set("exits", ([
                "north" : __DIR__"datiepu",
                "west" : __DIR__"ruzhou",
                "east" : __DIR__"dongmen",
        ]));


        set("outdoors", "ruzhou");
	set("coor/x", -6750);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
