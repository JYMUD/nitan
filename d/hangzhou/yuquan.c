// yuquan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "��Ȫ");
        set("long", @LONG
��Ȫ�½�����Ȫɽ�ϣ�ԭ�������¡��߽���Ȫ�£�ֻ�������м���ˮ��(pond)��
�������ǳ�����ɽ��·��
LONG);
        set("exits", ([
                "eastdown"  : __DIR__"road5",
                "north"     :  __DIR__"quanbian-xiaojing",
        ]));
        set("item_desc", ([
                "pond": "���Ե�ʯ�����š�������Ȫ��������ż��Сˮ����ӿ������һ������\n",
        ]));
        set("objects" , ([
                __DIR__"npc/you-ke" : 1,
                __DIR__"npc/yuenv"  : 1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 770);
	set("coor/y", -2010);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}