// gushanpingtai.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "��ɽƽ̨");
        set("long", @LONG
ƽ̨�����С��������¾���ͤ��ͤ��������һ����(duilian)��
���ﻹ������ˮ�أ��ٳ��е�ʯ��ɽ�����õøߵͲβ�������¡�
��������ɽ��·��
LONG);
        set("exits", ([
            "northdown" : __DIR__"gushan",
        ]));
        set("item_desc", ([
            "duilian" :
"ɽ              ��
ɽ              ��
ˮ              ��
ˮ              ��
��              ʱ
��              ʱ
��              ��
��              ��
��              ��
��              ��\n"
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 810);
	set("coor/y", -2040);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}