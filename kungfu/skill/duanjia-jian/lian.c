#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "�������" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg, skill;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || (query("skill_type", weapon) != "staff"
            && query("skill_type", weapon) != "sword") )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("duanjia-jian", 1) < 120)
                return notify_fail("��Ķμҽ���������죬����ʩչ" + name() + "��\n");

        skill=query("skill_type", weapon);

        if (me->query_skill_mapped(skill) != "duanjia-jian")
                return notify_fail("������û�м����μҽ�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "����һ���������²�������������֮�������е�" +
              weapon->name() + HIY "ʹ���������һ�㣬������$n" HIY "��\n" NOR;
        message_combatd(msg, me, target);

        addn("neili", -100, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) == 0 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(3));
        return 1;
}
