inherit ROOM;

void create()
{
        set("short", "�ϴ��");
        set("long", @LONG
���������ݳǵ��ϴ�֡���ȥ�����ݳ����ģ������Ǻ���ׯ������
Ҳû��ʲô���̣����������ݵ��ϳ��š�
LONG
        );

        set("exits", ([
                "north" : __DIR__"ruzhou",
                "south" : __DIR__"nanmen",
                "east"  : __DIR__"hong-damen",
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
