// Room: /d/suzhou/cangjingge.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "�ؾ���");
        set("long",@long
�м����������Ŵ���ܡ���������а������Թ��Ķ�����λ��ɮ��
ִ�������ڱ�Ŀ��˼��
long);
        set("exits",([
                "south" : __DIR__"dxbdian",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1119);
	set("coor/y", -1151);
	set("coor/z", 29);
	setup();
        replace_program(ROOM);
}