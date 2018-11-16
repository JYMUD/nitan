// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "��Ѫ��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int i, count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("xuedao-daofa", 1) < 180)
                return notify_fail("���Ѫ���󷨻������ң�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("��û�м���Ѫ����Ϊ����������ʩչ" + name() + "��\n");

        if( query("qi", me)<100 )
                return notify_fail("��Ŀǰ��Ѫ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("��Ŀǰ�������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "blade") + me->query_str() * 20;
        dp = defense_power(target, "dodge") + target->query_dex() * 20;

        msg = HIY "$N" HIY "��Ȼʩ����" HIR "��Ѫ��" HIY "��������" +
              weapon->name() + HIY "�����ޱ�ɱ�⣬Я�ŷ���֮����$n" HIY
              "��ն��ȥ��\n"NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 75,
                                           HIR "$n" HIR "ֻ����ǰһ��Ѫ����������"
                                           "���ѱ�$N" HIR "��һ�����˸����С�\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "ֻ��$P" CYN "������ӿ�����Եֵ�����"
                       "��������Ծ�����ߡ�\n" NOR;
        }

        msg += HIY "\n������$N" HIY "��Ŀ��ȣ�����" + weapon->name() +
               HIY "һ�񣬱ų�����Ѫ�⣬����ǵ�����$n" HIY "��\n"NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "��ʱ��$n" HIR "ֻ����Χɱ��������ȫ����Ѫ��"
                       "���������мܡ�\n" NOR;
                count = ap / 10;
        } else
        {
                msg += HIY "��ʱ��$n" HIY "ֻ����Χɱ���������ĵ�΢΢һ"
                       "������æ�����мܡ�\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(1 + random(3));
        addn("neili", -200-random(300), me);
        return 1;
}
