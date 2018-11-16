// liuxing.c ������˸

#include <ansi.h>

inherit F_SSERVER;

string name() { return "������˸"; }

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("��������˸��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        skill = me->query_skill("liushui-bian", 1);

        if (skill < 150)
                return notify_fail("�����ˮ�޷���Ϊ���������ڲ���ʹ�á�������˸����\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������޷����á�������˸����\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("��ʹ�õ��������ԣ�\n");

        msg = HIW "$N" HIW "��ʽͻȻ�ӿ죬�������е�" + weapon->name() +
              HIW "����ʱ���̻����Ű��������޻��������������$n"
              HIW "�����\n" NOR;

        message_combatd(msg, me, target);
        count = skill / 3;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))  break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(3));
        addn_temp("apply/attack", -count, me);

        return 1;
}
