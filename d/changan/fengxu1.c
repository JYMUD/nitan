//Room: fengxu1.c

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
                "west" : "/d/changan/baihu3",
                "south" : "/d/changan/fengxu2",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10700);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}