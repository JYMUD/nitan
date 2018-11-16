// jue.c ����ץ 

#include <ansi.h> 
#include <combat.h> 

inherit F_SSERVER; 

int perform(object me) 
{ 
        string msg; 
        object target; 
        int skill, ap, dp, damage; 

        if (! target) 
        {
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        }

        if (! target || ! me->is_fighting(target)) 
                return notify_fail("���������ҡ�ֻ����ս���жԶ���ʹ�á�\n"); 

         skill = me->query_skill("jimie-zhua", 1); 

        if( userp(me) && me->query_skill("jimie-zhua",1)<120 && !query("can_perform/jimie-zhua/wuwo", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");  

         if (skill < 100) 
                return notify_fail("��ļ���ץ�ȼ�����������ʹ�á��������ҡ���\n"); 

         if( query("neili", me)<250 )
                return notify_fail("�������������\n"); 

         if (me->query_skill_mapped("claw") != "jimie-zhua")  
                return notify_fail("��û�м�������ץ���޷�ʹ�á��������ҡ���\n"); 

         if (! living(target)) 
                 return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n"); 
         msg = HIY "$N" HIY "�͵�����ǰ����˫ץ����·$n" HIY "ץ����ƽ��" 
               "��һ����ȴ��ʾ����ʵ�Ļ�������\n" NOR; 

         ap = me->query_skill("force") + me->query_skill("claw"); 
         dp = target->query_skill("parry") + target->query_skill("dodge"); 
         if (ap / 2 + random(ap) > dp) 
         { 
                 addn("neili", -200, me);
                 damage = ap / 3 + random(ap / 4); 
                 msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55, 
                                            HIR "�����У�$p" HIR "�����м�$P�⿴��" 
                                            HIR "����һץ�������ץ�˸����У�" 
                                            "����һ����$p���϶���һ���˺ۡ�\n" NOR); 
                 me->start_busy(2); 
         } else 
         { 
                 msg += CYN "����$p" CYN "$P����������" CYN 
                        "��æ�мܣ�˳��Ծ����û�б�$P" 
                        CYN "���֡�\n" NOR; 
                  addn("neili", -20, me);
                  me->start_busy(3); 
          } 
          message_combatd(msg, me, target); 

           return 1; 
}
