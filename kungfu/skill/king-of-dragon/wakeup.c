// wakeup.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

int exert(object me, object target)
{
        if( (!target) || query("id", target) == query("id", me) )
                return notify_fail("��Ҫ����������˭��\n");
/*
        if( me->is_fighting() || target->is_fighting())
                return notify_fail("ս�����޷��˹����ˣ�\n");
*/
        if(target == me)
                return notify_fail("�㲻��Ϊ�Լ������Լ���\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("���������Ϊ������\n");

        if( query("neili", me)<1000 )
                return notify_fail("�������������\n");

        if( query("eff_qi", target)<query("max_qi", target)/5 )
                return notify_fail( target->name() +
                        "�Ѿ����˹��أ����ܲ�����������𵴣�\n");

        message_combatd(HIY "$N�������������ڹ�������������$n���ģ������ؽ���������$n����....\n\n���˲��ã�$N��ͷ��ð������ĺ��飬$n�³�һ����Ѫ����ɫ������������ˡ�\n$n���������ѹ�����\n" NOR, me, target );

        target->receive_curing("qi", 10 + (int)me->query_skill("force")/3 );
        addn("qi", 10+me->query_skill("force")/3, target);
        if( query("qi", target)>query("eff_qi", target))set("qi",query("eff_qi",  target), target);

           target->remove_call_out("revive");
           target->revive();
           target->reincarnate();
 
        addn("neili", -150, me);
        set("jiali", 0, me);
//                me->start_busy(5);
//                target->start_busy(5);
        return 1;
}