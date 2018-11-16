// dashouyin dashou-yin perform
// by dubei

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

int perform(object me, object target)
{
      string msg, dodge_skill;                                
      int damage, jiali, attack, defense, p;
      object armor;


      if (me->query_skill("buddhism", 1) < 300)
           return notify_fail("��ķ���Ϊ���㣬�޷�ʩչ�þ��У�\n");
      
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target) )
           return notify_fail("������ӡ��ֻ����ս���жԶ���ʹ�á�\n");        
      
      if( (int)me->query_skill("dacidabei-shou",1) < 120 )
           return notify_fail("��Ĵ�ȴ��ֲ�����죬����ʹ�á�����ӡ����\n");
      
      if( (int)me->query_skill("hand",1) < 120 )
           return notify_fail("��Ļ����ַ�������죬����ʹ�á�����ӡ����\n");

      if( (int)me->query_str() < 35 )
           return notify_fail("��ı�������ǿ������ʹ�á�����ӡ����\n");
      
      if( query("max_neili", me)<1200 )
           return notify_fail("�������̫��������ʹ�á�����ӡ����\n");
      
      if( query("neili", me)<800 )
           return notify_fail("�������̫���ˣ��޷�ʹ�ó�������ӡ����\n");   

      if( (int)target->query_condition("dashouyin"))
           return notify_fail("�Է��������С�����ӡ�������ˣ�\n");   
      
      if (me->query_skill_prepared("hand") != "dacidabei-shou")
           return notify_fail("�㻹û��׼����ȴ��֣��޷�ʩչ������ӡ����\n");   
          
      if( objectp(query_temp("weapon", me)) )
           return notify_fail("��������ʹ�á�����ӡ����\n");                                                                              
      jiali=query("jiali", me)+1;
      attack=query("combat_exp", me)/1000;
      attack += me->query_skill("hand");
      attack+=query("neili", me)/5;
      defense=query("combat_exp", target)/1000;
      defense += target->query_skill("dodge");
      defense+=query("neili", target)/7;
      attack = (attack+random(attack+1))/2;
      
      damage = me->query_skill("dacidabei-shou", 1)/40 * jiali;
      if(damage > 1500) damage = 1500;
      
      message_vision(HIR "\n$NͻȻ��ɫͨ�죬����Ĭ���������ԣ�˫�۹ǽ�һ���죬��Ȼ"
                     "�ڿն���������$n��ǰ��ȥ����һʽ������ӡ����\n"NOR,me,target);
 
      if( attack > defense ) { 
               if( objectp(armor=query_temp("armor/cloth", target) )
                   && query("armor_prop/armor", armor)<200
                  && damage > 500){
                        message_vision(HIY"ֻ���⶷�����ӡ����ӡ��$N��$n"HIY"�ϣ�Խ��Խ"
                                       "�󣬾�������÷��飬�ѳ�һ�����ڵ��ϣ�\n"NOR, target, armor);
                        armor->unequip();
                        armor->move(environment(target));
                        set("name", "�����"+query("name", armor), armor);
                        set("value", 0, armor);
                        set("armor_prop/armor", 0, armor);
                        target->reset_action();
                        }
               tell_object(target, RED"��ֻ���û����ؿ�һ���ʹ���Ѿ���������ǰ�أ�\n"NOR);
               target->receive_damage("qi", damage,  me);
         target->receive_wound("qi", damage/3, me);
         p=query("qi", target)*100/query("max_qi", target);

         msg = "( $n"+eff_status_msg(p)+" )\n";
         message_vision(msg, me, target);
         addn("neili", -jiali, me);
              }
      else {
               dodge_skill = target->query_skill_mapped("dodge");
         if( !dodge_skill ) dodge_skill = "dodge";
         message_vision(SKILL_D(dodge_skill)->query_dodge_msg(target, 1), me, target);
         }
      addn("neili", -200, me);
      me->start_busy(2+random(2));            
      return 1;
}

 