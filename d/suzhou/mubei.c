// Room: /d/suzhou/mubei.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "���鱮");
        set("long",@long
��ɽ֮����´�������ο������������������������λ��檵ĺ���
Ĺ��Ĺ�����ޱ�������׭������Т�ڻʵ����顰������������Ԫѫ֮��
�������ĳ���һ����ǧ���֣��Թųơ����µ�һ������
long);
        set("outdoors", "suzhou");
        set("exits",([
                "northeast" : __DIR__"shiyuan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1110);
	set("coor/y", -1160);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}