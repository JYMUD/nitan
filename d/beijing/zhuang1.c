#include <room.h>
inherit BUNCH_ROOM;

void create()
{
        set("short", "С·");
        set("long", @LONG
������һ��С·�ϡ�ǰ���·��᫣����˺��١�������һ������
��С��·��ɽ��
LONG );
        set("exits", ([
                "southwest" : "/d/beijing/road1",
                "north"     : "/d/beijing/zhuang2",
                "westup"    : "/d/beijing/shanlu1",
        ]));
        set("objects", ([
                "/d/taishan/npc/seng-ren" : 1,
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2780);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();
}
