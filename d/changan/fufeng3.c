//Room: fufeng3.c

inherit ROOM;

void create ()
{
        set ("short", "�����");
        set("long", @LONG
������ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·����
�˱ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء�������һ����·ͨ��
�����ǵ������š�
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "north" : "/d/changan/fufeng2",
                "south" : "/d/changan/fufeng4",
                "west" : "/d/changan/xian-dadao",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10740);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}