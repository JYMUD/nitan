//Room: liande-nankou.c

inherit ROOM;

void create ()
{
        set ("short", "�����Ͽ�");
        set("long", @LONG
����ֵĶ���ͷ��һ�����ɶ�ߵ����֮�ϣ���������յ�����
������ÿ��ĺɫ���٣�����ƻ�ͨ����������һ��С�ƹݣ���������
������ȭ���������������ͨ�����´����
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "west" : "/d/changan/huarui6",
                "north" : "/d/changan/liande-dadao5",
                "south" : "/d/changan/xiaojiuguan"
        ]));

        set("outdoors", "changan");  
        set("coor/x", -10680);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}