inherit ROOM;

void create()
{
        set("short", "��Ȫ��");
        set("long", @LONG
�㿴��һ����Ȫ�����������ǰ����������ð��������Ȫˮ����
Ȫ�䲻�󣬵�����ʹ���뵽��ȥ��һ�ݣ���˵�����������β���
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "northup" : __DIR__"lydao2",
                "eastup" : __DIR__"lydao3",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", -7130);
	set("coor/y", -2070);
	set("coor/z", -20);
	setup();
        replace_program(ROOM);
}