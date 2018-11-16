#include <ansi.h> 
#include <combat.h> 

#define HONG "��" HIR "��ϼ����" NOR "��" 

inherit F_SSERVER; 

int perform(object me, object target) 
{
        int skill, ap, dp, damage; 
        string msg; 
                object weapon;

        if( userp(me) && !query("can_perform/yecha-gun/hongxia", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n"); 

        if (! target) 
        { 
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        }

        if (! target || ! me->is_fighting(target)) 
                return notify_fail(HONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n"); 

        skill = me->query_skill("yecha-gun", 1);

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" HONG "��\n");
                
        if (skill < 120) 
                return notify_fail("���ҹ������ȼ�����������ʩչ" HONG "��\n"); 

        if( query("neili", me)<200 )
                return notify_fail("�����������������ʩչ" HONG "��\n"); 

        if (me->query_skill_mapped("club") != "yecha-gun") 
                return notify_fail("��û�м���ҹ�����������ʩչ" HONG "��\n"); 

        if (target->is_busy()) 
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n"); 

        if (! living(target)) 
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n"); 

        msg = HIR "$N" HIR "���������������" HIR "����ʵʵ����������Ĺ�Ӱ" 
              "��������ĺ�ϼ����$n���ذ�Χ��\n" NOR; 
        
        addn("neili", -50, me);

        ap = me->query_skill("club"); 
        dp = target->query_skill("parry"); 

        if (ap / 2 + random(ap * 4 / 3) > dp) 
        {
                addn("neili", -150, me);
                damage = ap / 8 + random(ap / 8); 
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30, 
                                           HIR "$n" HIR "ֻ��$N" HIR "��Ӱ���أ�" 
                                           "�������ڣ��Լ��޴���������ʱ����" 
                                           "���������������˸����ֲ�����\n" NOR); 

                me->start_busy(1); 
                if (ap / 2 + random(ap) > dp && ! target->is_busy()) 
                        target->start_busy(ap / 30 + 2); 
        } else 
        {
                msg += CYN "$n" CYN "ֻ��$N" CYN "�����˹����е���ʵ������" 
                       "���⿪����\n" NOR; 
                addn("neili", -80, me);
                me->start_busy(3); 
        } 
        message_combatd(msg, me, target);  

        return 1; 
}