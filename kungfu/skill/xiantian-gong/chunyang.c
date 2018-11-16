// powerup.c ���칦����

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ���ô��������������Լ���ս������\n");

        if( query("neili", me)<200 )
                return notify_fail("�������������\n");

        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ������ô����������ˡ�\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        message_combatd(HIY "$N΢һ�����������칦����׳�������ȫ������"
                        "�����������\n" NOR,me);
        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/dodge", skill*1/5, me);
        addn_temp("apply/parry", skill*1/5, me);
        set_temp("powerup", 1, me);

        me->start_call_out((:call_other, __FILE__, "remove_effect", me, skill * 2 / 5 :), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/dodge", -amount/2, me);
                addn_temp("apply/parry", -amount/2, me);
                delete_temp("powerup", me);
                tell_object(me, "������칦������ϣ��������ջص��\n");
        }
}