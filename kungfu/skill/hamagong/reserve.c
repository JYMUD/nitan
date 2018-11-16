// reserve.c ��󡹦������ת

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int a_amount);

int exert(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if ((int)me->query_skill("hamagong", 1) < 80)
                return notify_fail("��ĸ�󡹦������죬���ᾭ����ת��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ�����������\n");

        if( query_temp("hmg_dzjm", me) )
                return notify_fail("���Ѿ���ת�����ˡ�\n");

        skill = me->query_skill("hamagong", 1);
        msg = HIB "$N" HIB "����˫�ֳŵص��������˾�������ʱ"
              "��Ϣ������������������\n" NOR;
        message_combatd(msg, me);

        addn_temp("apply/dodge", skill/2, me);
        set_temp("hmg_dzjm", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 2 :), skill);

        addn("neili", -100, me);
        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("hmg_dzjm", me) )
        {
                addn_temp("apply/dodge", -amount, me);
                delete_temp("hmg_dzjm", me);
                tell_object(me, "��˫��һ�ţ�һԾ���𣬽������ջص��\n");
        }
}