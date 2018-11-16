// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "���ӡ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        skill = me->query_skill("dashou-yin", 1);

        if (skill < 100)
                return notify_fail("��Ĵ���ӡ��Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<150 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("hand") != "dashou-yin")
                return notify_fail("��û�м�������ӡ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("hand") != "dashou-yin")
                return notify_fail("��û��׼������ӡ������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "����ׯ�أ�����Я�ž��糯$n" HIY "��Ȼ�ĳ�����"
              "�����ھ�ѧ�����ӡ����\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -100, me);
                me->start_busy(2);
                damage = damage_power(me, "hand");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "���$p" HIR "�мܲ�������$P" HIR
                                           "��һ�´���������̣���Ѫ������\n" NOR);
        } else
        {
                addn("neili", -40, me);
                msg += CYN "����$p" CYN "���Ų�æ������ļܿ���$P"
                       CYN "�Ľ��ӡ��\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

