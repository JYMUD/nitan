// Room: /huanghe/shamo1.c
// Java. Sep 21 1998

#include <room.h>
#include <ansi.h>

inherit ROOM;
void create()
{
        set("short", "ɳĮ");
        set("long", @LONG
����һƬû�߼ʵ�ɳĮ�������ǽ����׸ߵľ޴�ɳ����һ�߽���
�ͷ·�����·�������и�ʯ����
LONG );
        set("exits", ([
                "north" : __DIR__"shamo",
                "south" : __DIR__"shamo",
                "east"  : __DIR__"shamo",
                "west"  : __DIR__"shamo",
                "enter" : __DIR__"shidong",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yongdeng");
        set("coor/x", -16070);
	set("coor/y", 4230);
	set("coor/z", 0);
	setup();
}
void init()
{
        object ob = this_player();
        if( query("water", ob)>10 )
                set("water",query("water",  ob)-10, ob);
        else
                set("water", 0, ob);
        message_vision(HIY"�����ɳ��$N�е�����ð�̣��ɿ��Ѱ���\n"NOR, ob);
}

int valid_leave(object me, string dir)
{
        int total_steps = random(9)+1;
        if ( dir == "north")
                addn_temp("shamo/steps", 1, me);
        if ( dir == "south")
                addn_temp("shamo/steps", -1, me);
        if( query_temp("shamo/steps", me) == total_steps )
        {
                me->move(__DIR__"jingyuan");
                delete_temp("shamo/steps", me);
                tell_object(me, "�����˰��죬�����߳�������ɳĮ��\n");
                return -1;
        }
        if( query_temp("shamo/steps", me) == -total_steps )
        {
                me->move(__DIR__"qingcheng");
                delete_temp("shamo/steps", me);
                tell_object(me, "�����˰��죬�����߳�������ɳĮ��\n");
                return -1;
             }
        return ::valid_leave(me,dir);
}