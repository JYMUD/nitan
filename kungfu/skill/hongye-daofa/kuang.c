//kuang.c 
// gladiator

#include <ansi.h>
#include <combat.h>

#define KUANG "��" HIR "�����Ҷ" NOR "��" 

inherit F_SSERVER;

int perform(object me, object target)
{
        int extra;
        object weapon;
        string msg;

        extra=me->query_skill("hongye-daofa",1);

        if( userp(me) && !query("can_perform/hongye-daofa/kuang", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if( !target ) target = offensive_target(me);

        if( !target||!target->is_character()||!me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ��" KUANG "��\n");

        if( (int)me->query_skill("hongye-daofa",1) < 150)
                return notify_fail("��Ŀǰ������ʹ����" KUANG "��\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "blade" )
                        return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("neili", me)<800 )
                        return notify_fail("�������������\n");
  if (! living(target)) 
         return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n"); 

        addn("neili", -300, me);
        msg = HIC "$N��ȻһЦ�����Ϳ�ݾ��׵ĵ�����Ȼ��ø���������\n"
              HIC "������һ˲֮�䣬$N��������ʮһ�����������ŷ磬���ﺬ�ŵ�Ӱ��\n"
              HIC "$nֻ����������ֹͣ�ˣ�" NOR;

        message_vision(msg, me, target);                
        
        message_combatd(HIY  "$N�����������ߵ���" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);

        message_combatd(HIY  "$N����$n�����������ߵ���" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);

        message_combatd(HIY  "$N��Ȼ�ִ����������ߵ���" NOR, me, target);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);

        me->start_busy(2 + random(2));
        return 1;
}