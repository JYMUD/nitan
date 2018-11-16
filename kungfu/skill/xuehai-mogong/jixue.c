// jixue.c Ѫ��ħ����Ѫ��

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        object weapon;  
        string msg;
        int skill;

        if( query_temp("jixue", me) )
                return notify_fail(HIG"���Ѿ������Ѫ���ˡ�\n");

        if (! me->is_fighting())
                return notify_fail("����Ѫ�󷨡�ֻ����ս����ʹ�á�\n");

        if( query("neili", me)<200 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("���Ѫ��ħ������Ϊ����������ʹ�ü�Ѫ�󷨣�\n");
        msg = HIR "$N" HIR "ʹ��Ѫ��ħ������Ѫ�󷨡���ɲʱ����ɫ���"
              "Ѫ�죬"HIR "$N" HIR "����ҧ����⣬���һ����Ѫ��\n" NOR;

        skill = (int)me->query_skill("xuehai-mogong", 1);

        if( query("qi", me)>query("max_qi", me)*6/10 )
        {       
                addn_temp("apply/damage", skill*20, me);
                addn_temp("apply/unarmed_damage", skill*20, me);
                set_temp("jixue", 1, me);
                me->start_call_out((: call_other, __FILE__, "remove_effect",
                                   me, skill :), skill);
                addn("neili", -150, me);
                me->receive_damage("qi",query("max_qi", me)/2);
        } else
                msg = HIR "$N" HIR "�����Լ��������ã�û�������Ѫ�󷨡�\n" NOR;

        message_combatd(msg, me);
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("jixue", me) )
        {
                addn_temp("apply/damage", -amount*20, me);
                addn_temp("apply/unarmed_damage", -amount*20, me);
                delete_temp("jixue", me);
                tell_object(me, "��ļ�Ѫ��������ϣ��������ջص��\n");
        }
}
