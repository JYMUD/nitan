// baiwei.c 
// gladiator

#include <ansi.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg; 
        object weapon;
        int extra;
        int count, i;

        extra = me->query_skill("huilong-zhang",1) + me->query_skill("staff", 1);    
        
        if (userp(me) 
        && me->query_skill("huilong-zhang", 1) <120
         && !query("can_perform/huilong-zhang/baiwei", me) )
                return notify_fail("�㻹����ʹ�á�������β����\n");            
        
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("��������β��ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(query_temp("weapon", me) || query("skill_type", weapon) != "staff") )
                return notify_fail("ʹ�á�������β��ʱ˫��Ӧ�ó��ȣ�\n");

        if( (int)me->query_skill("huilong-zhang", 1) < 80 )
                return notify_fail("��Ļ����Ȳ�����죬����ʹ�á�������β����\n");

        if( (int)me->query_skill("shaolin-xinfa", 1) < 80 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á�������β����\n");
     
        if( query("neili", me)<600 )
                return notify_fail("����������̫��������ʹ�á�������β����\n");

        msg = HIY "$N��Хһ�����������������и��ȣ�ͻȻһ��ת�����и��ȵ���$n��\n" NOR;

        message_vision(msg, me, target); 

        count = 3;
           
        for (i=0;i < count;i++)
        {
           COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        }

        addn("neili", -100*count, me);

        me->start_busy(1+random(2));

            return 1;
}
