#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string name() { return "��ղ���"; }
int perform(object me, object target)
{
        int skill;

        if( query("neili", me)<100 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("jingang-buhuaiti", 1) < 100)
                return notify_fail("��Ľ�ղ�����������Ϊ������\n");

        if( query_temp("jingangbuhuai", me) )
                return notify_fail("���Ѿ������ղ����������ˡ�\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIY "ֻ��$N" HIY "�ߺ���ţ�ȫ������������Ǽ�Ƥ��������ƽ�һ�㣬�����Ӳӽ�⡣\n" NOR, me);

        addn_temp("apply/armor", skill/2, me);
        addn_temp("apply/defense", skill/3, me);
        set_temp("jingangbuhuai", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("jingangbuhuai", me) )
        {
                addn_temp("apply/armor", -(amount/2), me);
                addn_temp("apply/defense", -(amount/3), me);
                delete_temp("jingangbuhuai", me);
                tell_object(me, "��Ľ�ղ���������������ϣ��������ջص��\n");
        }
}
