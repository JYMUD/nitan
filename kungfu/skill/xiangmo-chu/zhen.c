// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "�����" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "hammer" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("hammer") != "xiangmo-chu")
                return notify_fail("��û�м�����ս�ħ�ƣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("xiangmo-chu", 1) < 100)
                return notify_fail("���ս�ħ�ƻ���㣬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "һ���Ϻȣ�ʩ����" HIR "�����" HIY "������������"
              "ׯ�ϣ�������ǧ������" + weapon->name() + HIY "��$n" HIY "����"
              "���¡�\n" NOR;
        message_combatd(msg, me, target);

        addn("neili", -150, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(3));
        return 1;
}

