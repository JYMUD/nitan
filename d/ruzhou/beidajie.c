inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
���������ݳǵı���֡���ȥ�����ݳ����ģ���ȥ�����ݳǵı���
�ţ�����Ҳû��ʲô���̡�
LONG
        );

        set("exits", ([
                "north" : __DIR__"beimen",
                "south" : __DIR__"ruzhou",
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
