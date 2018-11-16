// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "�ý���" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill("tianyu-qijian", 1) < 120)
                return notify_fail("��������潣������죬����ʩչ" + name() + "��\n");

        if (me->query_skill("force", 1) < 160)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        level = me->query_skill("tianyu-qijian", 1);

        msg = HIY "$N" HIY "����Ϣ�������󼲶������ǧ�������������ǵط���$n"
              HIY "��\n" NOR;

        message_combatd(msg, me, target);
        addn("neili", -100, me);
        addn("apply/attack", level/2, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn("apply/attack", -level/2, me);
        me->start_busy(1 + random(2));

        return 1;
}
