// qixing. ���Ǿ�����

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon=query_temp("weapon", me);
        int damage;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("���Ǿ�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if( (int)me->query_skill("quanzhen-jianfa", 1) < 90 )
                return notify_fail("���ȫ�潣������������ʹ�������Ǿ�������\n");
  
    if( !weapon || query("skill_type", weapon) != "sword"
        || me->query_skill_mapped("sword") != "quanzhen-jianfa")
                return notify_fail("�������޷�ʹ�����Ǿ�������\n");

    if( query("neili", me)<200 )
                return notify_fail("��������������޷�ʹ�����Ǿ�������\n");

         msg = MAG "$Nһ����Х��һ�����н�����ʱ�γ�һ����Ļ����籩���ѹ��$n������
$n����֮�䣬��Ļ�зɳ��߶亮�ǣ������ǰ�����$n��\n";

        if( random(query("combat_exp", me))>query("combat_exp", target)/3){
                msg += "$n������������Ȼ�н���\n";
                damage = 3*(int)me->query_skill("quanzhen-jianfa", 1);
                damage = damage / 2 + random(damage / 2);
                if( damage>query("neili", target)/10 )
                        damage-=query("neili", target)/15;
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);
                 if( damage < 40 ) msg += HIY"$n���������������ϵ�����Ѫ��\n"NOR;
                 else if( damage < 80 ) msg += HIR"$n�����߽�����Ѫ���������\n"NOR;
                 else msg += RED"$n���ۡ��Ŀ��һ������������ߵ�Ѫ����\n"NOR;
                message_vision(msg, me, target);
        } 
        else {
                 msg += HIW"$n�鼱֮����󼤷ɣ����ſ�£����������������һ����\n" NOR;
                message_vision(msg, me, target);
        }
        addn("neili", -180, me);
        me->start_busy(2);

        return 1;
}
