// Room: /d/suzhou/shuchang.c
// Date: May 31, 98  Java
#include <room.h>;
inherit ROOM;

void create()
{
        set("short", "�鳡");
        set("long", @LONG
���߽��鳡�����������������ֵģ������ﶼ������ģ�����ǰ��
��һλ˵��������������ȥ����ʮ�꣬��������һ����壬���ھ۾���
���˵������--����ҽ�������Ҳ�𽥱���������������������е���
�ǲ�ʱ�ķ�����̾�ͺȲ�����ʱ��ʱ��ͭ��������ȥ��
LONG );
        set("outdoors", "suzhou");
        set("item_desc", ([
                "door" : "����һ��ͨ�����õ�Сľ�š�\n"
        ]));
        set("exits", ([
                "south" : __DIR__"xidajie2",
                "enter" : __DIR__"houtang",
        ]));
        set("objects", ([
                __DIR__"npc/gongzi": 1,
        ]));
        create_door("enter", "С��", "out", DOOR_CLOSED);
	set("coor/x", 1090);
	set("coor/y", -1050);
	set("coor/z", 0);
	setup();
}