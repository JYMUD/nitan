#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "͸�Ƕ�" NOR; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        weapon=query_temp("weapon", me);

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "dagger" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        skill = me->query_skill("qingliang-daxuefa", 1);

        if (me->query_skill("force") < 150)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (skill < 100)
                return notify_fail("��������Ѩ����Ϊ���ޣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("dagger") != "qingliang-daxuefa")
                return notify_fail("��û�м���������Ѩ��������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "��������" + weapon->name() + HIC "б�̶�����һʽ��"
              HIR "͸�Ƕ�" NOR + HIC "������ź�����������$n" HIC "��Χ������\n" NOR;

        ap = attack_power(me, "dagger");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                damage = damage_power(me, "dagger");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "��ʱֻ���á����͡�һ����$n" HIR
                                           "�ؿڱ�$N" HIR "��һ�д��У�����һ����Ѫ��\n" NOR);
                me->start_busy(1);
                if (ap / 3 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(ap / 80 + 1);
        } else
        {
                msg += CYN "����$p" CYN "�Ŀ�����$P" CYN
                       "����ʽ�������һһ��⣬û¶���"
                       "������\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}