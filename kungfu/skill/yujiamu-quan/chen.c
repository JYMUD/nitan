// fochen.c ����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "����"; }

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
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        skill = me->query_skill("yujiamu-quan", 1);

        if (skill < 100)
                return notify_fail("��Ľ�����ĸȭ��Ϊ����, �޷�ʹ�á���������\n");

        if( query("neili", me)<180 )
                return notify_fail("��������������޷����á���������\n");

        if( objectp(query_temp("weapon", me)) || query_temp("secondary_weapon", me) )
                return notify_fail("��������ֻ�ܿ������á�\n");

        if( angry=query("qi", me)<query("max_qi", me)/2 )
                msg = HIY "$N" HIY "Ŀ�����ѣ�һ�����ȣ�ȭͷ����������$n"
                      HIY "��Ҫ����\n" NOR;
        else
                msg = HIY "$N" HIY "���һ����ȭͷ����������$n"
                      HIY "��Ҫ����\n" NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                addn("neili", -150, me);
                me->start_busy(1);
                damage = damage_power(me, "cuff");
                if (angry) damage += random(damage / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "���$p" HIR "�޷��ֵ�$P"
                                           HIR "������һ������ʱ������������ҡ�β�����\n" NOR);
        } else
        {
                addn("neili", -40, me);
                msg += CYN "����$p" CYN "��δ�����������壬���ƽŲ����㿪��$P"
                       CYN "�Ĺ�����\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}