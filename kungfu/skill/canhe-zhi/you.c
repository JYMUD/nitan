// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return MAG "��ڤ����" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int i, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ��" + name() + "��\n");

        if ((int)me->query_skill("canhe-zhi", 1) < 120)
                return notify_fail("��Ĳκ�ָ��Ϊ���ޣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("��û�м����κ�ָ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "canhe-zhi")
                return notify_fail("������û��׼��ʹ�òκ�ָ������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "ֻ��$N" HIW "����һչ������Ȼ��ù����ޱȣ�������ָ��Ȼ��"
              "�������ɽ���ֱϮ$n" HIW "ҪѨ��ȥ��\n" NOR;

        message_combatd(msg, me, target);

        me->start_busy(1 + random(3));
        addn("neili", -300, me);
        level = me->query_skill("canhe-zhi", 1);
        addn("apply/attack", level/2, me);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn("apply/attack", -level/2, me);

        return 1;
}