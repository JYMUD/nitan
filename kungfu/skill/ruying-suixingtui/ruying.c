// gladiator

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int i; 

        i = me->query_skill("ruying-suixingtui", 1) / 4;

        if( userp(me) && !query("can_perform/ruying-suixingtui/ruying", me) )
                return notify_fail("����ʹ�õ��⹦��û�������Ĺ��ܡ�\n");
        
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("����Ӱ���Ρ�ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("ʹ�á���Ӱ���Ρ�ʱ˫�ֱ�����ţ�\n");

        if( (int)me->query_skill("ruying-suixingtui", 1) < 160 )
                return notify_fail("�����Ӱ�����Ȳ�����죬����ʹ�á���Ӱ���Ρ���\n");

        if( (int)me->query_skill("force", 1) < 160 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á���Ӱ���Ρ���\n");

        if( (int)me->query_dex() < 30 )
                return notify_fail("���������ǿ������ʹ�á���Ӱ���Ρ���\n");

        if (me->query_skill_prepared("unarmed") != "ruying-suixingtui"
        || me->query_skill_mapped("unarmed") != "ruying-suixingtui")
                return notify_fail("�������޷�ʹ�á�����ͬ�ԡ����й�����\n");
 
        if( query("max_neili", me)<2000 )
                return notify_fail("���������Ϊ̫��������ʹ�á���Ӱ���Ρ���\n");

        if( query("neili", me)<700 )
                return notify_fail("����������̫�٣�����ʹ�á���Ӱ���Ρ���\n"); 

        addn("neili", -500, me);
      
        msg = YEL "\n������һ�����������ھ���˲ʱ������\n" NOR;
        message_vision(msg, me, target); 
       
        addn_temp("apply/str", i, me);
        addn_temp("apply/dex", i, me);
        addn_temp("apply/attack", i, me);
        addn_temp("apply/damage", i, me);

        if( random(query("combat_exp", me))>query("combat_exp", target)/2
        &&  random((int)me->query_skill("force")) > (int)target->query_skill("force") / 2)
       { 
             msg = HIY "$N��ȻԾ�����һ��һ������ʱ֮���߳�һ�С��硹�־��Ĵ����ȣ�ֱϮ$nǰ�أ�"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);
        
             msg = HIY "������$N���ȹ��أ�������һŤ�������ȵ�һ�С�Ӱ���־���������������$n��"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),1,msg);
 
             msg = HIY"ֻ��$N�ҽž���δ���������һת������˳��ɨ��һ�С��桹�־�����Ӱ������"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);

             msg = HIY"�����$N��δ�󳷣��Ѿ������Ρ��־����ھ�ֱ͸�ż⣬��$n�ظ�����������ʮ�£�"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);

             msg = HIR"��ʱ$N˫��չ��������һ��ǿ�ҵ����磬˫����ʱ�벢������Ӱ���Ρ�һ�����ں���$n����֮�ϣ�"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);
        } else 
       {
             msg = HIY"$N��ȻԾ�����һ��һ������ʱ֮���߳�һ�С��硹�־��Ĵ����ȣ�ֱϮ$nǰ�أ�"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);
        
             msg = HIY"������$N���ȹ��أ�������һŤ�������ȵ�һ�С�Ӱ���־���������������$n��"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),1,msg);
 
             msg = HIY"ֻ��$N�ҽž���δ���������һת������˳��ɨ��һ�С��桹�־�����Ӱ������"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);

             msg = HIY"�����$N��δ�󳷣��Ѿ������Ρ��־����ھ�ֱ͸�ż⣬��$n�ظ�����������ʮ�£�"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),1,msg);
        }
 
             msg = YEL "\n����������ʹ�꣬ȫ��һת���������ڵ��ϡ�\n" NOR;
               
             addn("neili", -400, me);
             addn_temp("apply/dex", -i, me);
             addn_temp("apply/damage", -i, me);
             addn_temp("apply/str", -i, me);
             addn_temp("apply/attack", -i, me);
             me->start_busy(2+random(2));

        return 1;
}
