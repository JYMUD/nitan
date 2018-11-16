// feng.c

#include <ansi.h>
#include <combat.h>

string name() { return HIW "�������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 240)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill("xueshan-jian", 1) < 160)
                return notify_fail("���ѩɽ������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "xueshan-jian")
                return notify_fail("��û�м���ѩɽ����������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "ֻ��$N" HIW "һ����Х������" + weapon->name() +
              HIW "������ֹ���ų�����⻪��������������������ϯ��"
              "$n" HIW "��ȥ��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        damage = damage_power(me, "sword");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           HIR "$n" HIR "ֻ�к���Ϯ�壬ȫ��һ���"
                                           "�����ѱ�$N" HIR "�������ˡ���ʱ����һ"
                                           "�����һ�����Ѫ��\n" NOR);
        } else
        {
                addn("neili", -50, me);
                msg += CYN "����$n" CYN "����" CYN "$N" CYN
                       "������������Ծ���������ڽ���������"
                       "���������Ρ�\n"NOR;
        }

        msg = HIW"$N�漴��Хһ��������" + weapon->name() + HIW"�����������ѩ����ǰ����ǵص���ȥ��\n"
              "�ڰ�ãã��һƬ�У���Ȼ�������÷���ν�������͸ѩĻ��������˷����������\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           HIR "$n" HIR "ֻ���������������Լ�����˿˿������һʱȫ���ʹ����Ѫ�ɽ��õ������ǡ�\n" NOR);
        } else
        {
                addn("neili", -50, me);
                msg += CYN "����$p" CYN "˿����Ϊ$P"
                       CYN "�����Ľ������������Ƚ���һ���ܿ���\n" NOR;
        }
        me->start_busy(2 + random(2));
        message_combatd(msg, me, target);

        return 1;
}