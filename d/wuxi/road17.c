// Room: /d/wuxi/road17.c
// Winder 2000/02/22 

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "ɽ��");
        set("long", @LONG
ɽ·������ɽ�£��������ƽ̹Щ��������������ȥ����Ҫ�߲�
�������ɽ·������Щ�������ϵķ�����ɽ������ľ�дУ����»���
���ˣ�ֻ�����Ի������ѡ�
LONG );
        set("outdoors", "yixing");
        set("no_clean_up", 0);
        set("exits", ([
                "southdown" : __DIR__"road16",
                "northwest" : "/d/yixing/shanlu2",
        ]));
        set("coor/x", 980);
	set("coor/y", -720);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}