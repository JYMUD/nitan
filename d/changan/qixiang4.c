//Room: qixiang4.c

inherit ROOM;

void create ()
{
        set ("short", "�����");
        set("long", @LONG
������ǳ����Ǳ�һ��������Ĵ����������ྻ������ʮ��
���֣���������������Ϣ����ֵ������̼��Ƽ������СС�ĵ��̱�
�ڶ�����������һ��Ǯׯ�������������������Ľ���������
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/qunyulou",
                "north" : "/d/changan/bank",
                "west" : "/d/changan/beian-daokou",
                "east" : "/d/changan/qixiang5",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}