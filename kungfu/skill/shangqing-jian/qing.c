#include <ansi.h>
#include <combat.h>

string name() { return HIG "������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        string wname;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 220)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill("shangqing-jian", 1) < 160)
                return notify_fail("������彣����Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<400 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "shangqing-jian")
                return notify_fail("��û�м������彣��������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wname = weapon->name();

        damage = damage_power(me, "sword");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        msg = HIG "$N" HIG "ʩ�����彣����������������������" + wname +
              HIG "�漴һ������׼$n" HIG "������������ʽ�����ޱȣ�\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 20,
                                           HIR "$p" HIR "�����ֵ���ȴ�����мܵ�ס����$P"
                                           HIR "��һ������Ҫ������Ѫ�Ĵ��ɽ���\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "���������Ӳ������$P"
                       CYN "��һ���ܿ���˿������\n" NOR;
        }

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        msg += "\n" HIG "ȴ��$N" HIG "�粽��ǰ������" + wname +
               HIG "���ж��䣬�ֹ���һ��������������������⣬"
               "����$n" HIG "ȫ��\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                                           HIR "$p" HIR "ֻ���ۻ����ң�һʱ���Կ�͸��"
                                           "�а������������������Ѫ��ģ����\n" NOR);
        } else
        {
                msg += CYN "����$p" CYN "˿����Ϊ$P"
                       CYN "�����Ľ������������Ƚ���һ���ܿ���\n" NOR;
        }

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");
        msg += "\n" HIG "$N" HIG "�漴һ����ȣ����⻯�����⻯��������"
               + wname + HIG "��ʱ����һ����â���ٴι���$n" HIG "��ȥ��\n"
               NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$p" HIR "�����ֵ�����ֻ��һ�����ν���"
                                           "͸�����������֮�������������Ѫ��\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "һ�����Ե�������������$P"
                CYN "���彣â��Ȼ������ȴδ����$p" CYN "�ֺ���\n" NOR;
        }
        me->start_busy(2 + random(3));
        addn("neili", -300, me);
        message_combatd(msg, me, target);
        return 1;
}