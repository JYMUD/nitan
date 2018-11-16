// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ����ŭ�γ�ӿ�����Լ���ս������\n");

        if( query("neili", me)<500 )
                return notify_fail("�������������\n");

        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");

        addn("neili", -200, me);
        me->receive_damage("qi", 0);

        message_combatd(HIC "$N" HIC"һ����Х������һ���磬��"
                        "�˷���������������ɢ����\n��ʱ֮�䣬��"
                        "�Ƴ��綯�����ƾۺϣ������Ȼ�����纣"
                        "�����ϡ�\n" NOR, me);

        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/defense", skill*2/5, me);
        addn_temp("apply/unarmed_damage", skill*4, me);
        set_temp("powerup", 1, me);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int skill)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -(skill*2/5), me);
                addn_temp("apply/defense", -(skill*2/5), me);
                addn_temp("apply/unarmed_damage", -(skill*4), me);
                delete_temp("powerup", me);
                tell_object(me, "���ŭ�γ�ӿ������ϣ��������ջص��\n");
        }
}