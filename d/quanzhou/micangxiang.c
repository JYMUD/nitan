// Room: /d/quanzhou/micangxiang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "�ײ���");
        set("long", @LONG
����ͨ�����ֵ�С·���������˵��������ٹٸ����֣���������
ŭ֮�£��ؿ���·�������йٱ���Ԯ���֡�
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "southwest" : __DIR__"liangcang",
                "north"     : __DIR__"dudufu",
        ]));
	set("coor/x", -880);
	set("coor/y", -7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}