// shanlu6.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit BUILD_ROOM;
void create()
{
        set("short", "ɽ·");
        set("long", @LONG
ɽ·��᫣��������ӡ�������ľ�Դ䣬����ï�ܡ�ɽ·����һɽ
������˵������ʱ�ᴫ���������������ϻ�������������ɽ��·����
����ɽ�㵽��ɽ�ס�
LONG);
        set("exits", ([
            "eastup"  : __DIR__"yuhuangsd",
            "westdown": __DIR__"yuhuangshan",
        ]));
        set("objects", ([
            __DIR__"npc/laohu" : 1,
            __DIR__"obj/shuzhi" : 1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 770);
	set("coor/y", -2100);
	set("coor/z", 10);
	setup();
}