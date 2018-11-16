#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill, amount;

        if (target != me)
                return notify_fail("��ֻ����̫�����������Լ���ս������\n");

        if( query("neili", me)<100 )
                return notify_fail("�������������\n");

        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIW "$N" HIW "Ĭ��̫���������������������������پ�"
                        "ȫ���Ȼ�������᲻�ɴݡ�\n" NOR, me);
        //��ͨ�ζ�������Ч��
        
        if( query("breakup", me) )
        {    
                addn_temp("apply/attack", skill*2/3, me);
                addn_temp("apply/defense", skill*2/3, me);
                set_temp("powerup", 1, me);
        }
        else
        {
                addn_temp("apply/attack", skill/3, me);
                addn_temp("apply/defense", skill/2, me);
                set_temp("powerup", 1, me);
        }
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                if( query("breakup", me) )
                {
                        addn_temp("apply/attack", -(amount*2/3), me);
                        addn_temp("apply/defense", -(amount*2/3), me);
                }
                else
                {
                        addn_temp("apply/attack", -(amount/3), me);
                        addn_temp("apply/defense", -(amount/2), me);
                }
                delete_temp("powerup", me);
                tell_object(me, "���̫����������ϣ��������ջص��\n");
        }

}

