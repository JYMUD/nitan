//Room: qixiang1.c

inherit ROOM;

void create ()
{
        set ("short", "�����");
        set("long", @LONG
������ǳ����Ǳ�һ��������Ĵ����������ྻ������ʮ��
���֣���������������Ϣ����ֵ������̼��Ƽ������СС�ĵ��̱�
�ڶ������ֵı�����һ����¥��������һ�ҿ�ջ��
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/kezhan",
                "north" : "/d/changan/jiulou",
                "west" : "/d/changan/yongtai-beikou",
                "east" : "/d/changan/qixiang2",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10750);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}