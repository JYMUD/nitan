// huxiao.c ��Хɽ��
// gladiator

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;     
        int j, k;
        int i, count;
       
        j = me->query_skill("huzhua-claw", 1);
        k = me->query_skill("claw",1);

        if( userp(me) && !query("can_perform/huzhua-claw/huxiao", me) )
                return notify_fail("�㻹����ʹ�á���Хɽ�֡���\n");            
        
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("����Хɽ�֡�ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("ʹ�á���Хɽ�֡�ʱ˫�ֱ�����ţ�\n");

        if( (int)me->query_skill("huzhua-claw", 1) < 120 )
                return notify_fail("��Ļ�צ�����ֲ�����죬����ʹ�á���Хɽ�֡���\n");

        if( (int)me->query_skill("shaolin-xinfa", 1) < 120 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á���Хɽ�֡���\n");

        if( (int)me->query_dex() < 27 )
                return notify_fail("���������ǿ������ʹ�á���Хɽ�֡���\n");

        if (me->query_skill_prepared("claw") != "huzhua-claw"
        || me->query_skill_mapped("claw") != "huzhua-claw")
                return notify_fail("�������޷�ʹ�á���Хɽ�֡����й�����\n");                                                                                 
      

        if( query("neili", me)<600 )
                return notify_fail("����������̫��������ʹ�á���Хɽ�֡���\n");

        msg = HIR "$N��Хһ�����������������ģ����ͻ���ɽһ������$n��\n" NOR;


        if( random(10) >= 5 
        && !me->is_busy() 
        && j > 120
        && k > 120
        && j > random(target->query_skill("dodge",1)))
        {
          switch(random(3))
          {
            case 0 :
               msg  = HIB "$NĿ¶�׹⣬ʹ�����ڻ����ġ�������ץ��$n�ؿڣ�\n" NOR;
               msg += HIB "$n��$N�Ƶ��������ˣ��������У�\n" NOR;
               me->start_busy(3);
               message_combatd(msg, me, target);
               break;

            case 1 :
               msg  = MAG "$Nʩ�����������̡���˫�ַ׷ɣ��ó�������Ӱ��\n" NOR;
               msg += MAG "$nֻ���ۻ����ң���֪���롣\n" NOR;
               me->start_busy(1+random(2));
               message_combatd(msg, me, target);
               break;

            case 2 :
               msg  = BLU "$Nһ�С�����������������$n���ƺ�$n��ȫ������Ӱ���֣�\n" NOR;
               msg += BLU "$nֻ������Χȫ����Ӱ���֣����޶�������ء�\n" NOR;
               me->start_busy(random(3));
               message_combatd(msg, me, target);
               break;
          }
          count = 1;
          count += random(5);
          
          for (i=0;i < count;i++)
          {
           COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
          }
          addn("neili", -100*count, me);
       } else
       {
           msg += HIR "$nʶ�������ʽ���������������һ�ߡ�\n" NOR;
           me->start_busy(1 + random(2));
           addn("neili", -200, me);
        message_vision(msg, me, target);
       }  
       return 1;
}
