#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "�������Ծ�" NOR; }

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
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("force", 1) < 130)
                return notify_fail("����ڹ���򲻹���ʹ����" + name() + "��\n");

        if (me->query_skill("yinlong-bian", 1) < 100)
                return notify_fail("��������޷�����̫ǳ��ʹ����" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("��������������޷�ʹ��" + name() + "��\n");

        if (me->query_skill_mapped("whip") != "yinlong-bian")
                return notify_fail("��û�м��������޷���ʹ����" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "�����һЦ������" + weapon->name() +
              HIW "����һ��������Ȼ����$n" HIW "�����Ǿ����澭�е�"
             "���С�" HIC "�������Ծ�" HIW "����\n" NOR;

        ap = attack_power(me, "whip") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");
                addn("neili", -200, me);
                me->start_busy(2);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
                                           HIR "���$n" HIR "һ���ҽУ�δ�ܿ���$N"
                                           HIR "����ͼ������һ��Ӳ�����ؿڣ���Ѫ��"
                                           "����Ƥ��������\n" NOR);
                message_combatd(msg, me, target);

        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "����$p" CYN "����һԾ���𣬶�ܿ���"
                       CYN "$P" CYN "�Ĺ�����\n" NOR;
                message_combatd(msg, me, target);
        }

        return 1;
}