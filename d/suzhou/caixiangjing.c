// Room: /d/suzhou/caixingjing.c
// Last Modified by Winder on May. 15 2001

inherit ROOM;

void create()
{
        set("short", "���㾶");
        set("long",@long
������Ϊ���㾶���ֳơ�һ����������Ϫ�������������ʩ��ɽ֮
�ؾ�֮ˮ����Ҳ��Խ����ʱ�����Я��ʩ����С�۳���֮����
long);
        set("outdoors", "suzhou");
        set("exits",([
                "northeast" : __DIR__"shuiwa",
                "northwest" : __DIR__"shuiwa1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1120);
	set("coor/y", -1160);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}