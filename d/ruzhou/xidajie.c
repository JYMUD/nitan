inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
����������ݳǵ�֪�����ţ���Ȼδ��ʲô���ɣ��������Ե����
��ľ��ǽȴ���ֳ�һ�������������µĸо�����ȥ�����ݳ����ģ�����
Ҳû��ʲô���̡�
LONG
        );

        set("exits", ([
                "north" : __DIR__"yamen-damen",
                "south" : __DIR__"yingbin-lou1",
                "west" : __DIR__"ximen",
                "east" : __DIR__"ruzhou",
        ]));


        set("outdoors", "ruzhou");
	set("coor/x", -6770);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
