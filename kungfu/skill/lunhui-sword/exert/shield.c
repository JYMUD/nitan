
#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ���������ֻؽ��������Լ���ս������\n");

        if( query_temp("shield", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");

        message_combatd(HIR "$N" HIR "���������ֻ�������������ֻ������ƿ���ȥ��������ʣ�һ���������������Χ����$N" HIR "���ܡ�\n" NOR, me);

        // ��ͨBREAKUP���Ч������10%
        if( query("breakup", me))skill=skill+skill*1/10;
                
        addn_temp("apply/armor", skill/2, me);
        addn_temp("apply/parry", skill/10, me);
        set_temp("shield", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill :), skill / 2);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (! objectp(me))return;

        if( query_temp("shield", me) )
        {
                addn_temp("apply/armor", -(amount/2), me);
                addn_temp("apply/parry", -(amount/10), me);

                delete_temp("shield", me);
                tell_object(me, HIW "��������ֻؽ����񽣻��塹������ϣ��������ջص��\n" NOR);
        }


}