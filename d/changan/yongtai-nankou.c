//Room: yongtai-nankou.c

inherit ROOM;

void create ()
{
        set ("short", "��̩�Ͽ�");
        set("long", @LONG
����ֺ���̩����Ľ���ڣ�һ�����ɶ�ߵ����֮�ϣ�������
��յ����ĵ�����ÿ��ĺɫ���٣�����ƻ�ͨ����������һ�Ұ����̣�
����ͨ����̩�����
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "east" : "/d/changan/huarui1",
                "north" : "/d/changan/yongtai-dadao5",
                "south" : "/d/changan/baozipu"
        ]));

        set("outdoors", "changan");  
        set("coor/x", -10760);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}