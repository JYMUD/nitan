// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "�����" NOR; }

int perform(object me, object target)
{
        int lvl;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name()+"ֻ�ܿ���ʹ�á�\n");

        if( query_temp("gb_chanshen", target) )
                return notify_fail("�Է��Ѿ�����ʹ"+name()+"��ס�ˣ�\n");

        if (target->is_busy())
                return notify_fail("�Է�����æ���У����Ĵ󵨹����ɣ�\n");

        if ((int)me->query_skill("xiaoyaoyou", 1) < 150)
                return notify_fail("�����ң�β�����죬����ʹ��"+name()+"��\n");

        if ((int)me->query_skill("shexing-diaoshou", 1) < 150)
                return notify_fail("������е��ֲ�����죬����ʹ��"+name()+"��\n");

        if ((int)me->query_skill("huntian-qigong", 1) < 150)
                return notify_fail("��Ļ��������ȼ�����������ʹ��"+name()+"��\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("�������̫��������ʹ��"+name()+"��\n");

        if( query("neili", me)<200 )
                return notify_fail("�������̫���ˣ�����ʹ��"+name()+"��\n");

        /*
        if( !query_temp("gb_huixuan", me) )
                return notify_fail("��û��ʹ����ң���������޷�ʹ���������\n");
        */

        lvl = ((int)me->query_skill("xiaoyaoyou", 1) +
               (int)me->query_skill("shexing-diaoshou", 1)) / 2;

        message_combatd(HIB "\nͻȻ��$N���з�����˻˻����������˫�ְ�������ָ��������״��\n"
                        "�������ң������ͻȻ�۽�$n����ߣ���$n���һ����\n" NOR, me, target);

        addn("neili", -100+random(50), me);

        addn_temp("apply/defense", -lvl/3, target);
        addn_temp("apply/armor", -lvl/3, target);

        ap = attack_power(me, "hand");
        dp = defense_power(target, "dodge");
        if( ap / 2 + random(ap) > dp )
        {
                message_combatd(HIB "����$N������������Ы����һ�㣬����$n����ߣ���$n��֪���룬\n"
                                "ֻ���ķ·������ε�����������������$n��\n" NOR, me, target);

                target->start_busy(3 + random(lvl / 120));
        }

        set_temp("gb_chanshen", 1, target);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", target, lvl / 3 :), lvl / 25);

        return 1;
}

void remove_effect(object target,int lvl)
{
        if (! target) return;

        addn_temp("apply/defense", lvl, target);
        addn_temp("apply/armor", lvl, target);
        delete_temp("gb_chanshen", target);
        if (target->is_fighting())
        {
                // target->start_busy(1 + random(1));
                message_combatd(HIG "$Nʹ������������������������ε��ֵĹ�����С�\n" NOR, target);
        }
}
