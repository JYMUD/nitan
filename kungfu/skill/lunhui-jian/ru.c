#include <ansi.h> 
#include <combat.h> 

#define RU "��" HIR "�������" NOR "��" 

inherit F_SSERVER; 

string final(object me, object target, int damage); 

int perform(object me, object target) 
{
        object weapon; 
        string msg; 
        int ap, dp; 
        int damage; 

        if( userp(me) && !query("can_perform/lunhui-jian/ru", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me); 

        if (! target || ! me->is_fighting(target)) 
                return notify_fail(RU "ֻ�ܶ�ս���еĶ���ʹ�á�\n"); 

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" RU "��\n"); 

        if ((int)me->query_skill("lunhui-jian", 1) < 200) 
                return notify_fail("��������ֻؽ���������죬����ʩչ" RU "��\n"); 

        if( query("neili", me)<200 )
                return notify_fail("��������������������ʩչ" RU "��\n"); 

        if ((int)me->query_skill("buddhism", 1) < 200) 
                return notify_fail("�����ڶԷ�ѧ���򲻹�������ʩչ" RU "��\n"); 

        if (me->query_skill_mapped("sword") != "lunhui-jian")  
                return notify_fail("��û�м��������ֻؽ�������ʩչ" RU "��\n"); 

        if (! living(target)) 
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n"); 

        msg = HIC "$N" HIC "�������г�����һ��ȥ�Ƴ��ȣ�������ɨ��$n" 
              "�����Ʊ仯ƽƽ��\n" NOR; 

        addn("neili", -80, me);
        ap = me->query_skill("sword"); 
        dp = target->query_skill("parry"); 
        if (target->is_bad()) ap += ap / 10; 

        me->start_busy(2); 
        if (ap / 2 + random(ap) > dp) 
        {
                damage = ap + random(ap / 3); 
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75, 
                                           (: final, me, target, damage :)); 
        } else 
        {
                msg += HIC "����$n" HIC "��ʶ�㲩" HIC "�����ϵ�$P�����ı仯" 
                       "��ȫ��Ӧ�ԡ�\n" NOR; 
        } 
        message_combatd(msg, me, target); 

        return 1; 
}

string final(object me, object target, int damage) 
{
        target->receive_damage("jing", damage / 4, me); 
        target->receive_wound("jing", damage / 8, me); 
        return  HIC "$n" HIC "������ƽƽ��˿��δ�����з��������Ȼ$N" 
                HIC "����һ�䣬���г�\n����������������һ��һ���ı���$n��\n" NOR + 
                HIR "$n" HIR "����仯���޷�������ʱ��$P" HIR "��һ��ɨ��" 
                "��һ��Ѫ���Խ�â�м��������\n" NOR; 
}
