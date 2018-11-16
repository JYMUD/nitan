// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "��˿����" NOR; }

string final(object me, object target, int damage);

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

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name()+"ֻ�ܿ���ʩչ��\n");

        skill = me->query_skill("chansi-shou", 1);

        if (skill < 120)
                return notify_fail("���˿�����ֵȼ�����������ʩչ"+name()+"��\n");

        if (me->query_skill_mapped("hand") != "chansi-shou")
                return notify_fail("��û�м�����˿�����֣�����ʩչ"+name()+"��\n");

        if (me->query_skill_prepared("hand") != "chansi-shou")
                return notify_fail("��û��׼����˿�����֣�����ʩչ"+name()+"��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����ڵ���������������ʩչ"+name()+"��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "��Ȼ����$n" HIW "��ʩ����˿���ã�˫�ֺ�"
              "�ۺ�Ť����ץ��˦��ֱ��$p" HIW "����Ҫ����\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -80, me);
                damage = damage_power(me, "hand");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           (: final, me, target, damage :));
                me->start_busy(2);
        } else
        {
                msg += CYN "����$n" CYN "�Ŀ�����$N"
                       CYN "����ʽ��������мܲ�⣬û¶���������\n" NOR;
                addn("neili", -20, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        string msg;

        msg = HIR "ȴ��$n" HIR "�����ֿ������վ��޷�"
              "����$N" HIR "�Ĺ��ƣ��������ƣ�";

        if (random(3) >= 1 && ! target->is_busy())
        {
                target->start_busy(damage / 150);
                msg += "���Է�����\n" NOR;
        } else
                msg += "��Ѫ���硣\n" NOR;

        return  msg;
}