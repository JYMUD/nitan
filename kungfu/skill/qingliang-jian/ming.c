#include <ansi.h> 
#include <combat.h> 

#define SHENG "��" HIW "��������" NOR "��" 

inherit F_SSERVER; 

int perform(object me, object target) 
{ 
        object weapon; 
        string msg; 
        int ap, dp; 
        int damage; 

        
        if (! target) target = offensive_target(me); 

        if (! target || ! me->is_fighting(target)) 
                return notify_fail(SHENG "ֻ����ս���жԶ���ʹ�á�\n"); 

        if( userp(me) && !query("can_perform/qingliang-jian/ming", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");   

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" SHENG "��\n"); 

        if (me->query_skill("force") < 100) 
                return notify_fail("����ڹ�����Ϊ����������ʩչ" SHENG "��\n"); 

        if (me->query_skill("qingliang-jian", 1) < 80) 
                return notify_fail("�������������Ϊ����������ʩչ" SHENG "��\n"); 

        if (me->query_skill_mapped("sword") != "qingliang-jian") 
                return notify_fail("��û�м�����������������ʩչ" SHENG "��\n"); 

        if( query("neili", me)<80 )
                return notify_fail("��������������������ʩչ" SHENG "��\n"); 

        if (! living(target)) 
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n"); 

        msg = HIW "$N" HIW "һ������" + weapon->name() + HIW "����������������ͬʱ��$n" HIW "��ȥ��\n" NOR; 
        ap = me->query_skill("sword"); 
        dp = target->query_skill("parry"); 

        if (ap * 2 / 3 + random(ap) > dp) 
        {
                damage = ap / 3 + random(ap / 2); 
                addn("neili", -40, me);
                me->start_busy(2); 
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 20, 
                                           HIR "$n" HIR "����ͷ���ۻ�����֪��ʵ����ʱ$n" 
                                           HIR "���ϼ������ˣ�\n" NOR); 
        } else 
        {
                addn("neili", -20, me);
                me->start_busy(3); 
                msg += CYN "����$p" CYN "����������ʵ������ܿ���$P" 
                       CYN "�Ľ��С�\n"NOR; 
        }

        message_combatd(msg, me, target); 

        return 1; 
}
