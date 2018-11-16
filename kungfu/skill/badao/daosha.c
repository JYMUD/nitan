#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        int skill;
        object weapon;
        
        if( query("neili", me)<600 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("badao", 1) < 500)
                return notify_fail("��İԵ���Ϊ������\n");

        if (me->query_skill_mapped("blade") != "badao")
                return notify_fail("�㻹û�м����Ե��ء�\n");
                
        if( query_temp("badao-dasha", me) )
                return notify_fail("���Ѿ�ʩչ��ɷ�ˡ�\n");
                
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�\n");
                
        skill = me->query_skill("badao", 1);
        addn("neili", -500, me);

        message_combatd(HIY "$N�Ӷ�������" + weapon->name() + HIY "��һ��ǿ����������ȫ��ӿ��" + weapon->name() + 
                        HIY "����ʱ���������磬ɱ�����ڡ�\n" NOR, me);

        addn_temp("apply/damage", skill/2, me);
        set_temp("badao-dasha", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("badao-dasha", me) )
        {
                addn_temp("apply/damage", -(amount/2), me);
                delete_temp("badao-dasha", me);
                tell_object(me, "��İԵ�������ϣ��������ջص��\n");
        }
}