// tengshe.c ���߾�

#include <ansi.h>
#include <combat.h>

string name() { return WHT "���߾�" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "whip" )
                return notify_fail("��ʹ�õ��������ԣ��޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("ruanhong-zhusuo", 1) < 60)
                return notify_fail("����������������죬�޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("��������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("whip") != "ruanhong-zhusuo")
                return notify_fail("��û�м�������������޷�ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "��Ȼʩչ�������ߡ�������������һ����" + weapon->name() +
              WHT "��ʱ�εص�����ͬ����һ����ȻϮ��$n" + WHT "��\n" NOR;

        ap = attack_power(me, "whip") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "Ȼ��$n" HIR "δ�ܿ�����ͼ��һ���Һ���"
                                           + weapon->name() + HIR "�޶���û�����ڰ��"
                                           "����ʱ����������\n" NOR);
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "����$p" CYN "����������������ס��"
                       CYN "$P" CYN "�����Ī���һ����\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}