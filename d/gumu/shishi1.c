// Room: /d/gumu/shishi1.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
inherit ROOM;

void create()
{ 
        set("short",HIB"ʯ��"NOR);
        set("long", @LONG
��Ĺ��������ʯ�ң�ֻ����ԶԶ������Ų��Ļ������յ����ĸо�
ʹ������ֻ�п־壬�������ǹ¶����㲻֪���εأ�����������һ
Ƭ��ֻ�ܿ�����ǰ�С�
LONG        );
        set("exits", ([
                "east"  : __DIR__"shishi"+(1+random(3)),
                "west"  : __DIR__"shishi"+(1+random(3)),
                "south" : __DIR__"shishi"+(1+random(3)),
                "north" : __DIR__"shishi"+(1+random(3)),
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3210);
        set("coor/y", -40);
        set("coor/z", 80);
        setup();
}

void init()
{
        object me = this_player();
        if( userp(me) && query("jing", me)<200 )
        {
                me->move(__DIR__"shishi0"); 
                message("vision", me->name()+"�����������˹�����\n",environment(me), ({me}));
                write(HIR"�����������Լ�������֧.....\n"NOR);
                me->unconcious();
        }
        if( !query_temp("steps", me) && userp(me) )
                set_temp("steps", keys(query("exits"))[random(sizeof(query("exits")))], me);
}

int valid_leave(object me, string dir)
{
        if( dir != "up")
        me->receive_damage("jing", 10 + random(10));
        if( dir != query_temp("steps", me))set_temp("step", 0, me);
        else addn_temp("step", 1, me);
        if( query_temp("step", me)>3+random(3) )
        {
                me->move(__DIR__"shishi5");
                delete_temp("step", me);
                delete_temp("steps", me);
                me->start_busy(2);
                return notify_fail("���۵ð�������춷���ǰ����һ��������\n");
        }
        return ::valid_leave(me,dir);
}