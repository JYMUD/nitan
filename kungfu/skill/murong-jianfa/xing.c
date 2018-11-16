// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "��ת����" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("murong-jianfa", 1) < 80)
                return notify_fail("���Ľ�ݽ���������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "murong-jianfa")
                return notify_fail("��û�м���Ľ�ݽ���������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("dodge") < 120)
                return notify_fail("����Ṧ��Ϊ�������޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("��Ŀǰ����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIM "$N" HIM "ʹ��Ľ�ݼҾ�����" HIW "��ת����" HIM "��������"
              + weapon->name() + HIM "���ϱ������Ƿ�λ������������仯Ī�⣡\n" NOR;

        addn("neili", -210, me);

        message_combatd(msg, me, target);

        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (! target->is_busy() && random(2) == 1)
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 13);
        }

        me->start_busy(1 + random(3));

        return 1;
}
