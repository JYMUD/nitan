// wang.c ������ˮ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "������ˮ"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������ˮ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        ap = attack_power(me, "whip");

        if (ap < 180)
                return notify_fail("�����ˮ�޷��ȼ�����, ����ʹ�á�������ˮ����\n");

        if( query("neili", me)<200 )
                return notify_fail("��������������޷����á�������ˮ����\n");

        msg = HIC "$N" HIC "һ�����е�" + weapon->name() + HIC
              "�����һ��޻����漴�����ڱۣ������᳤���ֱ��$n" HIC
              "������\n" NOR;

        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp || ! living(target))
        {
                addn("neili", -150, me);
                damage = damage_power(me, "whip");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "���������ͣ�������������ʱ����"
                                           "�����У�����һ�����������ʹ��\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -40, me);
                msg += CYN "����$n" CYN "�������ƣ�����ܹ�$N"
                       CYN "��һ�С�\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
