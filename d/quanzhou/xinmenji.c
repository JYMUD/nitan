// Room: /d/quanzhou/xinmenji.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "���ż�");
        set("long", @LONG
����Ȫ�����涫�����һ���ɵ�����ģ�����ϱ��мҲ�ӣ�����
�����ŵ��ţ����������м���
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"taoranju",
                "south" : __DIR__"taocipu",
                "east"  : __DIR__"jishi",
                "west"  : __DIR__"diaoqiao",
        ]));
	set("coor/x", -910);
	set("coor/y", -7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}