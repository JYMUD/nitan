//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "����");
        set ("long", @LONG
һ��յ��������ӣ�������Ҳûһ�š���������ģ����ȴ�ֲ�����
�������˼�ͥ�þߣ������������һֱ����˿������С�
LONG);
        set("exits", ([ 
                "north" : __DIR__"kongwu1",
        ]));
        set("objects", ([ 
                __DIR__"obj/greenflower" : random(2),
        ]));
        set("no_clean_up", 0);
        set("coor/x", -7110);
	set("coor/y", -2100);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}