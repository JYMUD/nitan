// shanlu1.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit BUILD_ROOM;
void create()
{
        set("short", "ɽ·");
        set("long", @LONG
һ�������߳�����ɽ·�������������������졣����ɽ·�ϣ�ֻ
�����Է�����������ɫ���ˡ���ʱ�н���Ͳ�����������ϱ㵽����
���á����¾��Ǵ����
LONG);
        set("exits", ([
                "southup"   : __DIR__"fajingsi",
                "northdown" : __DIR__"road2",
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
	set("coor/x", 750);
	set("coor/y", -2060);
	set("coor/z", 10);
	setup();
}
