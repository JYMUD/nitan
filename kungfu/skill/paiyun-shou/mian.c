// This program is a part of NITAN MudLIB
// mian ���಻��


#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "���಻��"; }

int perform(object me, object target)
{
        string msg,x;
        int i,j,k,y;

        if( !target ) target = offensive_target(me);
        if( !target || !me->is_fighting(target) )
                return notify_fail("�����಻����ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("ʹ�á����಻����ʱ������֣�\n");

        if( (int)me->query_skill("paiyun-shou", 1) < 120 )
                return notify_fail("����������ֲ�����죬����ʹ�á����಻������\n");

        if( query("max_neili", me)<1100 )
                return notify_fail("������������Ϊ����������ʹ�á����಻������\n");

        if( query("neili", me)<500 )
                return notify_fail("����������̫��������ʹ�á����಻������\n");

        if( me->query_skill_prepared("hand") != "paiyun-shou"
        ||  me->query_skill_mapped("hand") != "paiyun-shou")
                return notify_fail("�����ȫ�������������֣�����ʹ�á����಻������\n");


        i = (me->query_skill("paiyun-shou", 1)/2);
        if( target->is_busy() ) i*=2;
        if( (int)me->query_skill("paiyun-shou", 1) > 400 )
        {
                y = 10;
        } else
        if( (int)me->query_skill("paiyun-shou", 1) > 180 )
        {
                y = 8;
        }
        else
        {
                y = 6;
        }
        msg = HIY "$N��Ȼ��������˫��Ȧ���������ʵ��������ա�һ���ĳ����ڶ��ƽ��������һ��"+chinese_number(y)+"�ƣ����������ƹ�����\n" NOR;
        message_combatd(msg, me, target);
        addn_temp("apply/attack", i, me);

        for(k = 0; k < y; k++)
        {
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        }
        addn_temp("apply/attack", -i, me);
        addn("neili", -400, me);
        me->start_busy(2);
        return 1;
}
