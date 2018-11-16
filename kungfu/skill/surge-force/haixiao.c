// powerup.c ����һХ

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount, int amount1);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ����ŭ�������������Լ���ս������\n");

        if( query("neili", me)<100 )
                return notify_fail("�������������\n");

        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIW "$N" HIW "���쳤Х��������ɽ�鱬������������Ѹ���α�ȫ����\n" NOR, me);

        if( query("can_perform/surge-force/new", me) ) skill *= 6; 
        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/defense", skill*2/5, me);
        addn_temp("apply/damage", skill*4, me);

        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill * 2 / 5, skill :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount, int amount1)       
{
        if (!me) return;
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                addn_temp("apply/damage", -amount1*4, me);
                
                delete_temp("powerup", me);
                tell_object(me, "���ŭ������������ϣ��������ջص��\n");
        }
}

