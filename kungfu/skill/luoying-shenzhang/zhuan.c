#include <ansi.h>
#include <combat.h>

string name() { return HIY "������ת" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("luoying-shenzhang", 1) < 120)
                return notify_fail("�����Ӣ���Ʋ�����죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("qimen-wuxing", 1) < 120)
                return notify_fail("����������е��о�����������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "luoying-shenzhang")
                return notify_fail("��û�м�����Ӣ���ƣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "luoying-shenzhang")
                return notify_fail("��û��׼����Ӣ���ƣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "���ƶ�Ȼһ�䣬ʩ����Ӣ���ơ�������ת������������"
              "ʵʵ�Ĺ���$n" HIY "��\n" NOR;

        ap = attack_power(me, "strike") +
             (int)me->query_skill("qimen-wuxing", 1) +
             me->query_int()*10;

        dp = defense_power(target, "parry") +
             (int)target->query_skill("qimen-wuxing", 1) +
             target->query_int()*10;

        addn("neili", -150, me);
        if (ap / 2 + random(ap) > dp)
        {
                target->start_busy(2 + random(3));
                me->start_busy(2);
                damage = damage_power(me, "strike");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "���һ������ʱ�������ƣ�"
                                           "�����һ����Ѫ�����Ӽ�ת����ͣ��\n" NOR);
        } else
        {
                me->start_busy(3);
                msg += HIC "����$p" HIC "������$P" HIC "����ͼ���������򣬱ܿ���$P"
                       HIC "��һ����\n"NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
