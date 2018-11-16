#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "����һ��" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("duanjia-jian", 1) < 80)
                return notify_fail("��Ķμҽ���������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "duanjia-jian")
                return notify_fail("������û�м����μҽ�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "һԾ��������һ�������һ�������Ľ���������$n"
              HIR "��ȥ��\n"NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "ֻ��$N" HIR "�˽���һ������$n"
                                           HIR "��$n" HIR "ֻ��һ���������Ķ�"
                                           "������ͷһ����Ѫ���������\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "����$p" CYN "�͵������һԾ��������$P"
                       CYN "�Ĺ�����Χ��\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
