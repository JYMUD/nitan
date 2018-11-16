#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ����̫�����������Լ��ķ�������\n");

        if( query("neili", me)<100 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("taixuan-gong", 1) < 40)
                return notify_fail("���̫�����ȼ�������\n");

        if( query_temp("shield", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_vision(HIG "$N" HIG "ĬĬ�˹����������͵�ʯ���ϵĿھ�һһ"
                        "���֣�̫�����ھ��ѻ���ȫ��\n" NOR, me);

        if( query("breakup", me) )
        {
                addn_temp("apply/armor", skill, me);
                set_temp("shield", 1, me);
        }
        else
        {
                addn_temp("apply/armor", skill/2, me);
                set_temp("shield", 1, me);
        }
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("shield", me) )
        {
                if( query("breakup", me) )
                        addn_temp("apply/armor", -amount, me);
                else                
                        addn_temp("apply/armor", -amount/2, me);
                delete_temp("shield", me);
                tell_object(me, "���̫����������ϣ��������ջص��\n");
        }
       
}

