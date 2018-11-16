// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "���޽���" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int angry;
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

        skill = me->query_skill("yujiamu-quan", 1);

        if (skill < 100)
                return notify_fail("�������ĸȭ��Ϊ����������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("cuff") != "yujiamu-quan")
                return notify_fail("��û�м���������ĸȭ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("cuff") != "yujiamu-quan")
                return notify_fail("��û��׼��������ĸȭ������ʩչ" + name() + "��\n");

        if( query("neili", me)<180 )
                return notify_fail("��Ŀǰ���������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        if( angry=query("qi", me)<query("max_qi", me)/2 )
                msg = HIR "$N" HIR "Ŀ�����ѣ�һ�����ȣ�ȫ�������ž���죬ȭ"
                      "ͷ����������$n" HIR "��Ҫ����\n" NOR;
        else
                msg = HIR "$N" HIR "���һ������ɫ��죬ȫ�������ž���죬ȭ"
                      "ͷ����������$n" HIR "��Ҫ����\n" NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -100, me);
                me->start_busy(1);
                damage = damage_power(me, "cuff");
                if (angry) damage += random(damage / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "���$p" HIR "�޷��ֵ�$P" HIR "����"
                                           "��һ������ʱ������������ҡ�β�����\n" NOR);
        } else
        {
                addn("neili", -40, me);
                msg += CYN "����$p" CYN "��δ�����������壬����"
                       "�Ų����㿪��$P" CYN "�Ĺ�����\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}