// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "�⻪��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, skill, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        skill = me->query_skill("shenghuo-ling",1);

        if (! (me->is_fighting()))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("��ʹ�õı������ԣ�����ʹ��ʥ���֮" + name() + "��\n");

        if (skill < 140)
                return notify_fail("���ʥ����ȼ�����, ����ʹ��ʥ���֮" + name() + "��\n");

        if (query("max_neili", me) < 1500)
                return notify_fail("���������Ϊ���㣬����ʹ��ʥ���֮" + name() + "��\n");

        if (query("neili", me) < 340)
                return notify_fail("�����������������ʹ��ʥ���֮" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "����һ������ʹ��ʥ���֮��" HIW "�⻪��" HIY "��������"
              + weapon->name() + NOR + HIY "������ɣ��ó���������"
              "â����$n" HIY "����������\n" NOR;

        ap = attack_power(me, "sword") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                       HIR "$n" HIR "ֻ�������â����ǵ�ϯ�������"
                       "��ȫ�޷��赲����ʱֻ��ȫ������ʹ����Ѫ��"
                       "��������\n" NOR);

                me->start_busy(2);
        } else
        {
                msg += CYN "����$n" CYN "��׼$N" CYN "���������͵���"
                       "ǰһԾ��������$N" CYN "�Ĺ�����Χ��\n"NOR;
                addn("neili", -150, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}
