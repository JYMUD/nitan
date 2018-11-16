// by sinb

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        int i;
        string msg;
        
        if (me->query_condition("killer") &&
            query("no_fight", environment(me)) )
        {
                tell_object(me, HIR "�㷢��������񹦺����ܵ����ƣ���Ѫδ���Զ��ָ���\n" NOR );
        }
        else
        {
                tell_object(me, HIR "������񹦷�������Ч���о���ʧ����Ѫ�������ָ���\n" NOR );
                message_vision(HIW "$N�۾������������â�����ϵ��˿��漣��������ˡ�\n" NOR, me);
        
                set("eff_qi",query("max_qi",  me), me);
                set("qi",query("eff_qi",  me), me);
                addn("neili", -100, me);
        }
        
        me->apply_condition("mingyu_qizu", duration - 1);
        
        if( duration < 1 ) 
        {
                message_vision(HIC "$N�ġ����㡹�湦������ϣ���ɫ��ʱһƬ�԰ס�\n" NOR, me);

                return 0;
        }
        return CND_CONTINUE;
}
