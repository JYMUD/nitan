inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����������������п׷����������ʵ۶������������˼������
���Լ��Ľ�ɽ��𢣬�����ʵ���ȻҲ�����⡣���ۺ��˵��ˣ����Ϲ��Ͼ�
��������ݡ�
LONG );
        set("exits", ([
                "west" : __DIR__"nroad3",
        ]));

        set("objects", ([
                "/d/beijing/npc/shusheng1" : 1,
                "/clone/misc/mazedoor" : 1,
        ]));

	set("coor/x", -6980);
	set("coor/y", 2210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}