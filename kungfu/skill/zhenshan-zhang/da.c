// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "��ɽ��ţ"; }

int perform(object me, object target)
{
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ɽ��ţֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�ø�ɽ��ţ��\n");

        if ((int)me->query_skill("zhenshan-zhang", 1) < 60)
                return notify_fail("�����ɽ�Ʋ�����죬����ʹ�ø�ɽ��ţ��\n");

        if( query("max_neili", me)<500 )
                return notify_fail("����ڹ���Ϊ���㣬�޷�ʩչ��ɽ��ţ��\n");

        if( query("neili", me)<150 )
                return notify_fail("����������̫�����޷�ʩչ��ɽ��ţ��\n");

        msg = WHT "$N" WHT "�Ŷ���������һ������ʹ����ɽ��ţ��˫�ƶ�׼$n"
              WHT "ƽƽ�Ƴ���\n" NOR;
        addn("neili", -100, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 50,
                                           HIR "$n" HIR "������æ���һ�ݣ����ֻ��"
                                           "�ؿ�һ�𣬶�ʱ����������ԭ��$N" HIR
                                           "���ھ����ˣ�\n"
                                           ":����@?");
                if (! target->is_busy())
                        target->start_busy(3 + random(2));
                me->start_busy(2);
        } else
        {
                me->start_busy(2);
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ����û���ϵ���\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}