// road14.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "��ʯ���");
        set("long", @LONG
�غ�����Ե������������ֹ��ӣ������۴��αȣ���������������
һƬ̫ƽ���־���������һ��԰�����˽���������ʮ�����֡�����
����ҽ�����࿪��ҩ�̡�
LONG);
        set("exits", ([
            "northeast" : __DIR__"road13",
            "southwest" : __DIR__"road15",
            "east"      : __DIR__"yaodian",
            "west"      : __DIR__"qingbomen",
        ]));
        set("objects", ([
            __DIR__"honghua/wen" :1,
            __DIR__"honghua/luo" :1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 820);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}