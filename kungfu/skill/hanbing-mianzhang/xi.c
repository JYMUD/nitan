// This program is a part of NITAN MudLIB
// xi.c ��Ѫ����

#include <ansi.h>

inherit F_SSERVER;

string name() { return "��Ѫ����"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, qi_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("hanbing-mianzhang", 1);

        if (! (me->is_fighting(target)))
                return notify_fail("����Ѫ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(weapon = query_temp("weapon", me)))
                return notify_fail("��ʹ����������\n");

        if (skill < 60)
                return notify_fail("��ġ��������ơ��ȼ�����, ����ʹ�á���Ѫ���𡹣�\n");

        if (me->query_skill("dodge", 1) < 200)
                return notify_fail("����Ṧ������û�д�ã��޷����á���Ѫ���𡹣�\n");


        msg = HIR "$N" HIR "ͻȻ��ͬ����һ����ٿ���۽�$n"
              HIR "����ǰ���������$n" HIR "���ʺ�ҧȥ��\n" NOR;
        message_combatd(msg, me, target);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                message_combatd(HIR"���һ����ҧ��$n�ľ��࣬����������һ����Ѫ��ʱ��$N��������������ɭ�ɲ���\n\n"NOR,me,target);

                if ( query("combat_exp", me) > random(query("combat_exp", target)*10) )
                {
                        message_vision(HIR"ֻ��$N�ĸ���΢΢����Ȼ��ſ�$n���ٿ�ʱ��$n�Ѿ�Ѫ�����ɣ�����������\n"NOR,me,target);
                        me->receive_curing("qi",query("max_qi", target)+100);
                        addn("qi",query("max_qi", target)+100, me);
                        target->receive_damage("qi", query("max_qi", target)+100, me);
                        target->receive_wound("qi", query("max_qi", target)+100, me);
                        target->die(me);
                }
                else
                {
                        message_vision(HIW"$nƴ����������������$N�Ŀ��ƣ������˼��أ���Ѫ�Ӿ�������������\n"NOR,me,target);
                        me->receive_curing("qi",query("max_qi", target)/3);
                        addn("qi",query("max_qi", target)/3, me);
                        target->receive_wound("qi", query("max_qi", target)/3, me);
                        if( !target->is_busy() )
                                target->start_busy(2);
                }

                me->start_busy(1 + random(2));
        } else
        {
                msg = CYN "ֻ��$n" CYN "���Ų�æ������һ���������$N"
                      CYN "�����ݣ�\n"NOR;
                addn("neili", -100, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}
