// shield.c ������
//

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ���ñ�а�����������Լ��ķ�������\n");

        if( query("neili", me)<100 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("pixie-jian", 1) < 50)
                return notify_fail("��ı�а������Ϊ������\n");

        if( query_temp("shield", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIW "$N" HIW "���Ӻ�ǰ���󣬺�����ң�һ"
                        "������˵�崷�ӿ����סȫ��\n" NOR, me);

        addn_temp("apply/armor", skill*3/2, me);
        set_temp("shield", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill * 3 / 2 :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        addn_temp("apply/armor", -amount, me);
        delete_temp("shield", me);
        tell_object(me, "��ı�а����������ϣ��������ջص��\n");
}
