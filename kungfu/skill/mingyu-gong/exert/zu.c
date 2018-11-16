// zu.c  by sinb

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ�������񹦻ָ��Լ�����Ѫ��\n");

        if( query("neili", me)<1000 )
                return notify_fail("�������������\n");

        if (me->query_condition("mingyu_qizu"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("mingyu-gong", 1);

        addn("neili", -100, me);

        message_combatd(HIC "$N" HIC "�������㡹�湦��"
                        "��������һƬ��â���漴�ָ�����\n" NOR, me);


        me->apply_condition("mingyu_qizu", skill / 100);
        if (me->is_fighting()) me->start_busy(5);

        return 1;
}
