//Room: fengxu2.c

inherit ROOM;

void create ()
{
        set ("short", "��ڼ��");
        set("long", @LONG
��ڼ���ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·����
�˱ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء�
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "north" : "/d/changan/fengxu1",
                "south" : "/d/changan/fengxu3",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10700);
	set("coor/y", 1940);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}