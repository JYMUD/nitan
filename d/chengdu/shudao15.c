#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
�����������������µ�����ϣ�����������·�Ϸ�Ҫ����С�ģ�
�þ�ȫ���������С�����һ�������;��ú����ˡ�
LONG );
        set("exits", ([
                "westup" :  __DIR__"shudao16",
                "eastdown" : __DIR__"shudao14",
  
        ]));        
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15120);
	set("coor/y", -1830);
	set("coor/z", -30);
	setup();
}

int init()
{
        object me;
        int i;
        me = this_player();
    i=query("max_qi", me)/50;
        me->receive_damage("qi", i);
        tell_object(me, HIR "���������������ϣ��۵�����������\n" NOR);
}