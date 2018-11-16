// This program is a part of NITAN MudLIB
// huaxue.c

#include <ansi.h>

#define HUAXUE "��" HIR "�񵶻�Ѫ" NOR "��"

inherit F_SSERVER;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        object weapon;
        string msg;
        int skill;

        if( query_temp("huaxue", me) )
                return notify_fail(HIG "���Ѿ�����" + HUAXUE + HIG "�ˡ�\n");

        /*
        if (! me->is_fighting())
                return notify_fail(HUAXUE + "ֻ����ս����ʹ�á�\n");
        */

        if( query("neili", me)<200 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("�����ȿ�ս����Ϊ����������ʹ��" + HUAXUE + "��\n");

        weapon=query_temp("weapon", me);

        if( !objectp(weapon) || query("skill_type", weapon) != "blade" )
                return notify_fail("��û��װ����������ʩչ" + HUAXUE + "��\n");

        msg = HIR "$N" HIR "�����Ŀ�����ֳֵ�������˳��" + weapon->name() +
              HIR "����һĨ����Ѫ��ʱ��" + weapon->name() + HIR "Ⱦ�졣\n����$N"
              HIR "˫Ŀ��������ʱɱ�����죡\n" NOR;

        skill = (int)me->query_skill("moshen-xinfa", 1);

        addn("neili", -150, me);
        addn_temp("apply/damage", skill*5, me);
        addn_temp("apply/unarmed_damage", skill*5, me);
        addn_temp("apply/blade", skill, me);
        set_temp("huaxue", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill :), skill);

        message_combatd(msg, me);
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("huaxue", me) )
        {
                addn_temp("apply/damage", -amount*5, me);
                addn_temp("apply/unarmed_damage", -amount*5, me);
                addn_temp("apply/blade", -amount, me);
                delete_temp("huaxue", me);
                tell_object(me, "���" + HUAXUE + "������ϣ��������ջص��\n");
        }
}