// This program is a part of NT MudLIB

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIR"Ǳ��"NOR);
        set("long", @LONG
��û��ˮ�У�ֻ��ˮ��������������޷����㡣�������쳣��ֻ��������
��Ǳ�У������ǽ���ά�ȡ�ͻ���������й�ǿ���������������³�,�㲻�����������³�ȥ.
LONG
        );

        setup();
}

void init()
{
        object me;
        me = this_player();
        me->receive_damage("qi", 500 );
        me->receive_damage("jing", 500 );
        message_vision(HIB"$N������������ʧ������ʮ�����ѡ�\n"NOR, me);
        call_out("down", 5, me);
        if( query("qi", me)<10 || query("jing", me)<10 )
        {
                set_temp("die_reason", "��Ǳ���б�����", me);
                me->unconcious();
                me->die();
                return ;
        }
}

void down(object me)
{
        tell_object(me, "ֻ���ŵ�ˮ��������һ��ǿ�����������������ȥ...\n");
        me->move(__DIR__"hedi");
}
