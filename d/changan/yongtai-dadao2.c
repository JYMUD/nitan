//Room: yongtai-dadao2.c

inherit ROOM;

void create ()
{
        set ("short", "��̩���");
        set("long", @LONG
���ڽֵ������ϱ��������еĴ�֣��Ͷ����Ķ������ֻ��ཻ��
���ɡ���������������ʵ�ҹ����ȴ�������������ƻ�ͨ��������һ
�����֡�����С�ֺ��������Щ���ֽ����ã���Ȼ���򡣶��洫
��һ����������ĺ�������֪����ʲô�ط���
LONG );
        set("exits",([//sizeof() == 2
                "south" : "/d/changan/yongtai-dadao3",
                "north" : "/d/changan/yongtai-dadao1",
                "east"  : "/d/pk/entry",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10760);
	set("coor/y", 1940);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}