// xiaohua.c �ﻨ���
// Modified by whuan
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        object weapon;
        int i,j,k,damage;
        if( !target ) target = offensive_target(me);

        if (!objectp(weapon = me->query_temp("weapon")) 
         || (string)weapon->query("skill_type") != "sword")
        if (!objectp(weapon = me->query_temp("secondary_weapon"))
         || (string)weapon->query("skill_type") != "sword")
                return notify_fail("�������޽������ʹ�����������ľ�����У�\n");
    
        if( time() < 10+(int)me->query_temp("xiaohua") )        
                return notify_fail("���ʹ���ﻨ��š����У���Ѫ��ӿ���޷����У�\n");    
    
        if ( (int)me->query("neili") <500)
                return notify_fail("��������������޷�ʹ�����ﻨ��š���\n");
        
        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("���ﻨ��š�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("yuxiao-jian", 1) < 100 )
                return notify_fail("������｣��������죬����ʹ�á��ﻨ��š���\n");

        if( (int)me->query_skill("bibo-shengong", 1) < 100 ) 
                return notify_fail("��ı̲�����Ϊ�������޷����á��ﻨ��š����С�\n");

        me->set_temp("xiaohua",time());
       
        j=1+me->query_skill("sword")/50; 
        if (j>7) j=7; //���㽣��
        k=(int)me->query_skill("sword");
        damage = k+random(k/2) + me->query_temp("apply/damage");
        damage = damage*11/20;//�����˺�
        
        msg = CYN "$Nʹ�����｣�����С��ﻨ��š�������һԾ������"+chinese_number(j)+"��������$n��\n";
        message_vision(msg, me, target);

        for (i=0;i<j;i++)
        {
		       if (random(me->query_skill("sword")+target->query_skill("dodge"))>target->query_skill("dodge")) 
		       {
			       message_vision(HIY"\n$nһ������������һ����\n"NOR,me,target);
             target->receive_damage("qi",damage,me);
             target->receive_wound("qi",damage/6+random(damage/6),me); 
			       COMBAT_D->report_status(target);
            }
		       else
             message_vision(HIY"\n$n�����������ò����ײűܿ�����һ����\n"NOR,me,target);
         }

        me->start_busy(1+random(2));
        me->add("neili",-30*j);
        return 1;
}
