// Room: /d/suzhou/hanshidian.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "��ʰ��");
        set("long", @LONG
���﹩�����ഫΪ���ͺ϶��ɡ�����ĺ�ɽ��ʰ�ý���������̬
����������ϲ������ɽ��ÿ���Ϧ��ҹ��ײ��һ������죬�京���ǳ�
��ӭ�ºͼ������һ�����λ��ɮ��
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out"   : __DIR__"fengqiao",
                "west"  : __DIR__"zhengdian",
        ]));
	set("coor/x", 1049);
	set("coor/y", -1051);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}