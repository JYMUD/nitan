// This program is a part of NITAN MudLIB
// �������µ���ն.����

#include <ansi.h>
#include <combat.h>

string name() { return HIY "ն"HIR"."HIY"��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 180)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill("mingyue-blade", 1) < 120)
                return notify_fail("����������µ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<1200 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "mingyue-blade")
                return notify_fail("��û�м����������µ�������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


        msg= HIC "$N" HIC "����ӿ��������������۳�ɳ����ɱ����ǧ������֮���׳���黳��һ����Х����ض��𣬼����������$n��ȥ��\n"
             HIC "ͬʱ������" + weapon->name() + HIC"�ɺ�ڱ��ֱָ��ǿ���ɭ�����ǵĵ�����$n��ӿ��ȥ��\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -240, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 210,
                                           HIR "$n" HIR "����������˸����ĵ�����"
                                           "��ʱ������ǰһƬ���⣬��Ȼ��֪��ζ�ܣ�\n" NOR);
                me->start_busy(2);
                if (ap / 3 + random(ap / 2) > dp && ! target->is_busy())
                        target->start_busy(3);
        } else
        {
                msg += CYN "$p" CYN "���һ����Ҳ���мܣ��������"
                       "�������ߣ��ܿ���$P" CYN "��һ�С�\n" NOR;
                addn("neili", -120, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}

