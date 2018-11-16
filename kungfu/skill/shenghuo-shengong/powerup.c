#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ����ʥ�����������Լ���ս������\n");

        if ((int)query("neili", me) < 150)
                return notify_fail("�������������\n");

        if ((int)query_temp("powerup", me))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        addn("neili", -150, me);
        message_combatd(HIM "$NĬ��ʥ���񹦣���ɫ���ɻƷ��ϣ����������Ϸ��������������죬����ֻ�"
                        "��Ϊ��ɫ����Ϊ���졣\n" NOR,me);
        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/dodge", skill*2/5, me);
        addn_temp("apply/parry", skill*2/5, me);
        set_temp("powerup", 1, me);

        me->start_call_out((:call_other, __FILE__, "remove_effect", me, skill * 2 / 5 :), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if (query_temp("powerup", me))
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/dodge", -amount, me);
                addn_temp("apply/parry", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "���ʥ����������ϣ����������˿������������ջص��\n");
        }
}
