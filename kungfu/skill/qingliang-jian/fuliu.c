//������
//edit by gladiator

#include <ansi.h>
#include <combat.h>


#define FULIU HIG "����������" NOR
inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon; 

        if ( !target ) target = offensive_target(me);
        weapon=query_temp("weapon", me);

        if( !userp(me) && me->query_skill("qingliang-jian")<100 && !query("can_perform/qingliang-jian/fuliu", me) )
              return notify_fail("��ʹ�õ��⹦��û�����ֹ��ܣ�\n");
              
        if ( !target || !target->is_character() || !me->is_fighting(target) )
              return notify_fail(FULIU + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ( (int)me->query_skill("qingliang-jian", 1) < 80 )
              return notify_fail("�������������������������ʹ��" + FULIU + "��\n");

        if ( (int)me->query_skill("force", 1) < 80 
         || (int)me->query_skill("shaolin-xinfa",1 ) < 80)
              return notify_fail("���Ƿ�Ӧ�����ڹ���Ϊ�϶��µ㹦��\n");

        if( query("max_neili", me)<1000 )
              return notify_fail("���������Ϊ�������ߡ�\n");

        if( query("neili", me)<300 )
              return notify_fail("�����������ʹ��" + FULIU + "��\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"
        || me->query_skill_mapped("sword") != "qingliang-jian" )
              return notify_fail("��Ľ���������������\n");
        
        if (! living(target)) 
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n"); 
 
        msg = HIG "\n$N�������������������������������ƳԱ��˷�ķ���һ�㣬"
                  "Ȼ��ȴ����һ���������˸е�����Ͱ��ݣ�\n"
                  "����һ��������һ����紵���һƬ����Ҷ������$n��\n" NOR;

        if( random(query("combat_exp", me))>query("combat_exp", target)/3 )
        { 
                me->start_busy(3);
                target->start_busy(random(2));

                damage = (int)me->query_skill("qingliang-jian", 1) + 
                         (int)me->query_skill("dodge", 1) / 2;
                         
                damage = damage /2 + random(damage);
//                target->receive_damage("qi", damage * 2)
//                target->receive_wound("qi", damage)
                
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, damage / 2,
                        GRN "$n������" + FULIU + GRN "����һ�����ؿڻ���һ���������˿ڣ�"
                           "��ʱ��Ѫ���������\n" NOR);
   
                message_vision(msg, me, target);
                COMBAT_D->report_status(target);    
                return 1;
        } else
        {
                me->start_busy(3);
       
                msg += HIG"$n���÷�������æ����������������$N�Ľ�����Χ��\n"NOR;
        }
                
        addn("neili", -150, me);
        message_vision(msg, me, target);

        if ( !target->is_fighting(me)) target->fight_ob(me);
        return 1;
}
