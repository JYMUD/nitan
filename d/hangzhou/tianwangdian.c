// tianwangdian.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "������");
        set("long", @LONG
�߽���ֻ����������̻��¶�������շ��������Ĵ�������
��������̬���ϵ�Τ��������������������Ǵ��۱��
LONG);
        set("exits", ([
                "out"       : __DIR__"lingyinsi",
                "north"     : __DIR__"dxbaodian1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 739);
	set("coor/y", -2051);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}