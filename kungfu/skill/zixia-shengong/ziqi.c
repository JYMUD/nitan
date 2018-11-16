// ziqi.c ��������
// looo/2001/6/21/update
#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        object weapon;
        string msg;
        int d_count, count, qi, maxqi, skill;

        if( query_temp("ziqi", me) )
                return notify_fail(HIG"���Ѿ����������������ˡ�\n");

        if( query("neili", me)<200 )
                return notify_fail("���������������\n");

        if( (int)me->query_skill("force") < 150)
                 return notify_fail("�����ϼ�񹦵���Ϊ����������ʹ����������! \n");

        //�����б������ӱ�������
        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��û�н�.��ô����������ѽ? \n");

        msg = MAG "$N" MAG "����һ����,����������ʢ!!���еı�������͸��һ���Ϲ�..\n" NOR;

        qi=query("qi", me);
        maxqi=query("max_qi", me);
        skill = (int)me->query_skill("zixia-shengong", 1);

        if(qi > (maxqi * 0.4))
        {
                message_combatd(msg, me);
                addn_temp("apply/damage", skill*5, me);
                addn_temp("apply/sword", skill/10, me);
                set_temp("ziqi", 1, me);
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill/5);

                addn("neili", -150, me);
        }
        else{
                msg = HIR "$N" HIR "ƴ�����������������������������Լ�����̫�أ�û�ܳɹ�!\n" NOR;
                message_combatd(msg, me);
        }

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("ziqi", me) )
        {
                addn_temp("apply/damage", -amount*5, me);
                addn_temp("apply/sword", -amount/10, me);
                delete_temp("ziqi", me);
                tell_object(me, HIY "������������������,����������ȥ.\n" NOR);
        }
}