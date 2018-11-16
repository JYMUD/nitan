// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "����ָѨ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        skill = me->query_skill("canhe-zhi", 1);

        if (skill < 120)
                return notify_fail("��Ĳκ�ָ��Ϊ���ޣ�����ʩչ" + name() + "��\n");

        if( query("neili", me)<150 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("��û�м����κ�ָ, ����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "canhe-zhi")
                return notify_fail("������û��׼��ʹ�òκ�ָ, ����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "һ����ߣ�������ʳ��ָ��£��ббָ������$n"
              HIG "���������¡�\n" NOR;

        addn("neili", -120, me);

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "���ֻ���������ۡ�������$p" HIR "����$P"
                       HIR "��ָ����סѨ�����������á�\n" NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ������һԾ���㿪����һ�С�\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}