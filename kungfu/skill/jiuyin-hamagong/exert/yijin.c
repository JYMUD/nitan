// yijin.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int skill);

int exert(object me, object target)
{
        int skill, n;

        if (target != me)
                notify_fail("��ֻ�ܶ��Լ���["+WHT+"�׾�ת��"+NOR+"]���������ѵ�ս���ͷ�������\n"NOR,);

        if( query("neili", me)<500 )
                return notify_fail("�����������!");
        if( userp(me) && !query("can_perform/jiuyin-hamagong/yijin", me) )
                      return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n"); 

        if( query_temp("yijin", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        n = skill / 5;

        addn("neili", -400, me);
        me->receive_damage("qi", 0);

        message_combatd(HIY "$N" HIY "��������һ������ͻȻ˫�Ƴŵأ�˫�ų��ϣ�ֻ"
                        "��ȫ���������������������в�ͣ���أ���ɫ������ϣ�\n" NOR, me);

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill/3, me);
        addn_temp("apply/dodge", skill/3, me);
        addn_temp("apply/parry", skill/3, me);
        addn_temp("apply/armor", skill/3, me);
                addn_temp("apply/damage", skill/2, me);
        addn_temp("apply/dispel_poison", skill/3, me);
        addn_temp("apply/reduce_poison", 15, me);//���15%�Ŀ���

        set_temp("yijin", skill, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill :), n);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int skill)
{
        skill=query_temp("yijin", me);
        
        if( query_temp("yijin", me) )
        {
                addn_temp("apply/attack", -(skill/3), me);
                addn_temp("apply/defense", -(skill/3), me);
                addn_temp("apply/dodge", -(skill/3), me);
                addn_temp("apply/parry", -(skill/3), me);
                addn_temp("apply/armor", -(skill/3), me);
                addn_temp("apply/damage", -(skill/2), me);
                addn_temp("apply/dispel_poison", -(skill/3), me);
                addn_temp("apply/reduce_poison", -15, me);
                delete_temp("yijin", me);
                tell_object(me, "���["+HIR+"�׾�ת��"+NOR+"]������ϣ��������ջص��\n");
        }
}

