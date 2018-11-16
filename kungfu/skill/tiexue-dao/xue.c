#include <ansi.h>
#include <combat.h>

string name() { return HIR "Ѫ������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("tiexue-dao", 1) < 100)
                return notify_fail("����Ѫ�����ȼ�����������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "tiexue-dao")
                return notify_fail("��û�м�����Ѫ����������ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 150)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("��Ŀǰ���������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "ɱ����ʢ������" + weapon->name() +
              HIR "һ�񣬶�ʱһ��Ѫ��ӵ�����������$n"
              HIR "���Ź�ס��\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           HIR "ֻ��$n" HIR "һ���Һ�������һ����"
                                           "һ��Ѫ����" HIR "Ѫɫ��Ӱ�м��������"
                                           "\n" NOR);
                me->start_busy(2);
                addn("neili", -120, me);
        } else
        {
                msg += CYN "����$n" CYN "�����ֿ죬�����мܣ���$N"
                       CYN "����ʽȫ��������\n" NOR;
                me->start_busy(3);
                addn("neili", -80, me);
        }
        message_combatd(msg, me, target);

        return 1;
}