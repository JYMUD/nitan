//Room: xian-dadao.c

inherit ROOM;

void create ()
{
        set ("short", "�������");
        set("long", @LONG
�����ǵ��������������Ϊ���֣����˱��ǵľ����⣬���в���
�������ÿͺ����ˡ�����������������ǳ����ǵ���̩���ڡ������ţ�
�����ǹʻʹ��ķ������
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "east" : "/d/changan/fufeng3",
                "west" : "/d/changan/xian-daokou",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10750);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}