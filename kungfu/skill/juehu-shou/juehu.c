// juehu.c ��צ�����֡�������
// by Lonely

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        int damage, ap, dp;
        string msg, pmsg;
        
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("���˵�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�á��������񹦣�\n");  
                
        if( (int)me->query_skill("juehu-shou", 1) < 100 )
                return notify_fail("��Ļ�צ�����ֲ�����죬����ʹ�á���������\n");

        if( (int)me->query_skill("taiji-shengong", 1) < 100 )
                return notify_fail("���̫���񹦲����ߣ������á����������˵С�\n");

        if( query("shen", me)<10000 )
                return notify_fail("��а��̫�أ��޷�ʹ������������ʽ��\n");

        if( query("neili", me)<400 )
                return notify_fail("����������̫��������ʹ������������ʽ��\n");

        msg = BLU "$NĬ���񹦣���ɫ�׵����ˣ�ͻȻʹ����צ�����ֵ����һ��������������ͼ������$n����ץ�¡�\n" NOR;
        
        
        addn("shen", -8000, me);
        me->want_kill(target);
                              
        ap = attack_power(me, "claw"); 
        dp = defense_power(target, "force"); 

        if (ap / 2 + random(ap) > dp) 
        {       
                damage = damage_power(me, "claw");
                addn("neili", -300, me);
                pmsg = RED "���$Nһ�����У�$nֻ�е�����һ���ʹ�����ھ�Ԫ������й����ʱ������֫���������Ȳ�ͣ������\n" NOR;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50, pmsg);

                me->start_busy(3);
                target->start_busy(3);                
                
        } else 
        {
                addn("neili", 150, me);
                msg += CYN "����$p" CYN "������$P" CYN "�ĺݶ���ͼ�����������������㿪��$P" CYN "������һ����\n" NOR;
                me->start_busy(4);
        }
        
        message_combatd(msg, me, target);
        
        if (damage > 200)
        {
                target->apply_condition("juehu_hurt",(500*query("age", target)));
                if( query("gender", target) == "����" )
                {
                        message_combatd(HIW "$NͻȻ���ĵ����ڵľ�Ԫ����ʧ�ʾ�������һ���ѹ���֪���Լ���һ��ʱ�䲻���л�������!\n" NOR, target);
                } else
                {
                        if( query("gender", target) == "Ů��" )
                                message_combatd(HIW "$N����һ�����У�������������ŭ����$n����һŮ��֮��Ҳ�ô�����������\n"NOR,
                                                target,me);
                        else
                                message_combatd(HIW "$N��Ȼ����$n��Ҫ�������о��������ᣬ�ƺ�����Ҫ������!\n"NOR,
                                me,target);
                }
          
        }
        
        if (! target->is_killing(me))
                target->kill_ob(me);
        return 1;
}
