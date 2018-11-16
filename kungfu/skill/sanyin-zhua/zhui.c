// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "׷��צ" NOR; }

int perform(object me, object target)
{
        object weapon;
        int level;
        int i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("ֻ�п��ֲ���ʩչ" + name() + "����\n");

        if (me->query_skill_mapped("claw") != "sanyin-zhua")
                return notify_fail("�����õĲ����������צ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("claw") != "sanyin-zhua")
                return notify_fail("�������Ĳ����������צ������ʩչ" + name() + "��\n");

        /*
        if (me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("�����õĲ��ǻ����󷨣�ʩչ����" + name() + "��\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 120)
                return notify_fail("�㻯������Ϊ̫���������" + name() + "��\n");
        */

        if (me->query_skill("sanyin-zhua", 1) < 120)
                return notify_fail("���������צ��Ϊ̫���������" + name() + "��\n");

        if( query("neili", me) <= 400 )
                return notify_fail("�����������ʹ��׷��צ��\n");

        message_combatd(HIB "$N��Ȼ�ٺٸ�Ц������˫����������ϻ�ɳ�������˿�����Ҫ�Ӻδ����У�\n"
                        "ͻȻ$N���һ������δͣӰ��������$n������˫צ��ץ��צ������֮����$n�޴Ӷ�����\n"
                        NOR, me, target);

        level = me->query_skill("sanyin-zhua", 1) + me->query_skill("finger", 1);

        addn_temp("apply/attack", level, me);
        addn_temp("apply/unarmed_damage", level, me);

        for (i = 0; i < 5 + random(5); i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn_temp("apply/attack", -level, me);
        addn_temp("apply/unarmed_damage", -level, me);

        me->start_busy(2 + random(2));
        return 1;
}
