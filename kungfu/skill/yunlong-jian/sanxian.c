#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int i,lvl;
        
        if( !target ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("���������֡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("yunlong-jian", 1) < 120 )
                return notify_fail("���������������̫ǳ���������ˡ�\n");

        if( (int)me->query_skill("sword", 1) < 120 )
                return notify_fail("��Ļ�����������̫ǳ���������ˡ�\n");
                        
        if( query("max_neili", me)<1200 )
                return notify_fail("�������̫ǳ���������ˡ�\n");
                
        if( query("neili", me)<500 )
                return notify_fail("��������������������ˡ�\n");
                
        if( me->query_skill_mapped("force") != "yunlong-shengong" &&
            me->query_skill_mapped("force") != "jiuyang-shengong") 
            
                return notify_fail("����ʲôΪ������ʹ����������ô?\n");
        if( !(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "sword"
            || me->query_skill_mapped("sword") != "yunlong-jian")
                return notify_fail("��ʹ��������������ô?\n");
                
        lvl = ( (int)me->query_skill("yunlong-jian", 1) + (int)me->query_skill("force", 1) ) /8;
        
        addn("neili", -300, me);
        message_combatd(HIR "\n$N��Цһ��������һ����" + weapon->name() + HIR"���������죬��������һ�㡣\n"
                "ͻȻ�佣��һ��������ֻ�������ꡱ�������죬 $N����һ˲����$n����������������Ѱ����\n"NOR, 
                me, target);
                
        addn_temp("apply/dex", lvl, me);
        addn_temp("apply/damage", lvl, me);
        addn_temp("apply/str", lvl, me);
        addn_temp("apply/attack", lvl, me);
        
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        
        addn_temp("apply/damage", -lvl, me);
        addn_temp("apply/str", -lvl, me);
        addn_temp("apply/dex", -lvl, me);
        addn_temp("apply/attack", -lvl, me);
        
        me->start_busy(3);
        return 1;
}
