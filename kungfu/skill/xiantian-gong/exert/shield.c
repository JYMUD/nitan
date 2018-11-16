// shield.c �����޼���

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int a_amount);

int exert(object me, object target)
{
        int skill;
        string msg;

        if ((int)me->query_skill("xiantian-gong", 1) < 50)
                return notify_fail("������칦���������\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ�����������\n");

        if( query_temp("shield", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");

        msg = HIW "$N" HIW "��������һ������˫��һ��һ�ɻ���������"
              "ʱ������������ܡ�\n" NOR;
        message_combatd(msg, me);

        addn_temp("apply/armor", skill/2, me);
        set_temp("shield", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me,
                              skill / 2 :), skill);

        addn("neili", -100, me);
        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("shield", me) )
        {
                addn_temp("apply/armor", -amount, me);
                delete_temp("shield", me);
                tell_object(me, "�������޼�����ת��һ�����죬�������ջص��\n");
        }
}