// kuang.c -������ʮһʽ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "����ʮһʽ"; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á�����ʮһʽ����\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                    return notify_fail("��ʹ�õ��������ԣ�\n");

        if (me->query_skill_mapped("blade") != "kuangfeng-blade")
                return notify_fail("��û�м������쵶���޷�ʩչ��\n");

        if ((int)me->query_skill("kuangfeng-blade", 1) < 150)
                return notify_fail("��Ŀǰ������ʹ����������ʮһʽ����\n");

        if( query("neili", me)<300 )
                return notify_fail("�������������\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -200, me);
        msg = HIW "\n$N" HIW "��ȻһЦ�����Ϳ�ݾ��׵ĵ�����Ȼ��"
              "�ø���������������һ˲֮�䣬$N" HIW "��������ʮ"
              "һ����\n�������ŷ磬���ﺬ�ŵ�Ӱ��$n"
              HIW "ֻ����������ֹͣ�ˣ�\n" NOR;

        if (random(10) < 2)
        {
                if (random(10) < 7) me->start_busy(1);
                else
                {
                        me->start_busy(2);
                }
        }
        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");

        if (ap * 3 / 4 + random(ap) > dp)
        {
                if (random(3) == 1) target->start_busy(2);
                damage = damage_power(me, "blade");
                damage += random(damage);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "ֻ��$n" HIR "�ѱ�$N" HIR
                                           "�е����������Ѫ�������ȫ�����������\n" NOR);
        } else
        {
                msg += HIC "����$p" HIC "��æ����㿪��ʹ$P"
                       HIC "����û�еóѡ�\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
