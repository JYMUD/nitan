// shanlu7.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit BUILD_ROOM;
void create()
{
        set("short", "ɽ·");
        set("long", @LONG
ɽ·��᫣��������ӡ�������ľ�Դ䣬����ï�ܡ�ɽ·���Ǻ���
ͤ�������ＫĿԶ����Ⱥɽ���������۵ס���������ɽ��·��������
����ɽ��·��
LONG);
        set("exits", ([
            "eastdown": __DIR__"yuhuangsj",
            "westup"  : __DIR__"yuhuangsd",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 790);
	set("coor/y", -2100);
	set("coor/z", 10);
	setup();
}
