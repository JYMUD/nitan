//Room: yongtai-dadao4.c

inherit ROOM;

void create ()
{
        set ("short", "��̩���");
        set("long", @LONG
���ڽֵ������ϱ��������еĴ�֣��Ͷ����Ķ������ֻ��ཻ��
���ɡ���������������ʵ�ҹ����ȴ�������������ƻ�ͨ��������һ
�����֡�����С�ֺ��������Щ���ֽ����ã���Ȼ���򡣶�����
һ��������
LONG );
        set("exits",([//sizeof() == 3
                "south" : "/d/changan/yongtai-dadao5",
                "north" : "/d/changan/xian-daokou",
                "east" :"/d/changan/miao"
        ]));

        set("outdoors", "changan");
        set("coor/x", -10760);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
        