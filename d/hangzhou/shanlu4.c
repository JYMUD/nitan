// shanlu4.c
#include <room.h>
inherit BUILD_ROOM;
void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����������С·�ϣ�������;ɽ����Ӱ��������У���ʯ�߲���
�����е��ػ��泩�����ϱ㵽�������á����¾͵���������
LONG);
        set("exits", ([
            "westup"   : __DIR__"faxisi",
            "eastdown" : __DIR__"shanlu5",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
	set("coor/x", 760);
	set("coor/y", -2110);
	set("coor/z", 50);
	setup();
}
