// This program is a part of NITAN MudLIB
// leiting.c  �������֡�����һ����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "����һ��"; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("������һ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("paiyun-shou", 1) < 100)
                return notify_fail("����������ֲ�����죬����ʹ�á�����һ������\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�á�����һ������\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹����޷�ʹ�á�����һ������\n");

        if( query("neili", me)<500 )
                return notify_fail("�����������������޷�ʹ�á�����һ������\n");

        msg = HIG "$N" HIG "����������˫�ƣ�һ��ŭ�ȣ�˫����Ȼ��������$n" HIG "�Ƴ���\n" NOR;

        ap = attack_power(me, "hand") +
             me->query_str()*20;

        dp = defense_power(target, "parry") +
             target->query_str()*20;

        addn("neili", -150, me);

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                damage = damage_power(me, "hand");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "���ܲ���������ǰ�أ�"
                                           HIR "ֻ�����ء���һ����$n"
                                           HIR "����һ����Ѫ��������ֽ�װ����ɳ���\n" NOR);
                me->start_busy(2);
        } else
        {       msg += HIC "����$p" HIC "���з�����" HIC
                       "����һ�����ܿ���$P" HIC "��һ����\n"NOR;
                me->start_busy(2);
        }
        message_vision(msg, me, target);
        return 1;
}
