#include <ansi.h>

#define BATTLEFIELD2_D     "/adm/daemons/battlefieldd2.c"
inherit ITEM;

void delay_destruct()
{
        destruct(this_object());
}

void init(object me)
{
        object target;
        string* players;

        if( !me ) me = this_player();
        if( !userp(me) ) 
                return;

        if( !BATTLEFIELD2_D->in_battle(me) )
                return;

        if( query_temp("used") )
                return tell_object(me, name(1)+"��ǿ�������Ѿ���ʹ�á�\n");

        players = BATTLEFIELD2_D->get_sorted_players();

        for(int i=0;i<sizeof(players);++i)
        {
                if( players[i] == me->query_id(1) )
                        continue;

                target = find_player(players[i]);
                if( !objectp(target) || !BATTLEFIELD2_D->inside_battlefield(target) )
                        continue;

                if( objectp(target) && BATTLEFIELD2_D->in_battle(target) )
                        break;
        }

        BATTLEFIELD2_D->add_bonus_score(me, 100);
        tell_object(me, "����Ϊ����"+name(1)+"����� "HIY"100"NOR" ��ս��������\n");
        if( target )
        tell_object(me, "�㴥����ս���־�ʯ����������"+target->query_idname()+NOR"�������������\n");

        tell_object(target, HIR+me->query_idname()+HIR"ʹ����ս���־�ʯ������������������������\n" NOR);
        target->set_weak(10);

        call_out((: delay_destruct :), 0);

        set_temp("used", 1);
}

void create()
{
        set_name(RED"ս���־�ʯ��"NOR, ({ "battlefield fear statue", "statue" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "ʹ�����ʯ�����˿��Դ��������һλս������ҵ�������");
                set("value", 1000000);
                set("unit", "��");
                set("no_get", 1);
        }
}

