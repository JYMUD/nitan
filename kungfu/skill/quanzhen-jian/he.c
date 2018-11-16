// This program is a part of NT MudLIB
// hebi.c ȫ�潣֮����Ů�����

#include <ansi.h>

inherit F_SSERVER;

string name() { return "˫�����"; }

void check_fight(object me, object target, object victim, int amount);
private int remove_effect(object me, int amount);

int perform(object me, object target)
{
        int skill, skill1, skill2;
        object victim;
        object weapon;

        if( !victim ) victim = offensive_target(me);

        if( !victim || !victim->is_character() || !me->is_fighting(victim) )
                return notify_fail("˫�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !target )
                return notify_fail("������˭����˫����赣�\n");

        if( query("id", victim) == query("id", target) )
                return notify_fail("��������˽���˫����赣�\n");

        if( !target->is_fighting(victim) )
                return notify_fail("��������˫����赵Ķ���δ����ĵ��˲�����\n");

        if( target->query_skill_mapped("sword") != "yunv-jian" )
                return notify_fail("��������˫����赵Ķ�����ʹ�õĲ�����Ů������\n");

        if( !objectp(weapon=query_temp("weapon", target) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("��������˫����赵Ķ���û���ý���\n");

        if( query_temp("hebi", me) )
                return notify_fail("������"+target->name()+"����˫����赡�\n");

        if( query_temp("hebi", target) )
                return notify_fail("��������˫����赵Ķ����������˺ϱ�ս���У���Ͼ�����赣�\n");

        if( query_temp("yunv_hebi", target) )
                return notify_fail("��������˫����赵Ķ���������������Ů��ȫ�潣�������У����������赣�\n");

        skill1 = me->query_skill("sword");
        skill2 = target->query_skill("sword");
        skill =  ( skill1 + skill2 ) / 4;

        if( mapp(query("couple", me)) &&
            query("couple/couple_id", me) == query("id", target) )
        skill += skill/2;

        message_combatd(
        HIR "\n$N��$nͻȻ��˫��һ����ȫ�潣������Ů������ϵ������޷죬���Ƽ�������Ȼ������\n\n" NOR, me, target);

        addn_temp("apply/attack", skill/2, me);
        addn_temp("apply/damage", skill, me);
        addn_temp("apply/dodge", skill/2, me);
        addn_temp("apply/parry", skill/2, me);
        set_temp("hebi", 1, me);

        addn_temp("apply/attack", skill/2, target);
        addn_temp("apply/damage", skill, target);
        addn_temp("apply/parry", skill/2, target);
        addn_temp("apply/dodge", skill/2, target);
        set_temp("hebi", 1, target);

        addn_temp("apply/damage", skill, me);
        addn_temp("apply/damage", skill, target);
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        COMBAT_D->do_attack(target,victim,query_temp("weapon", target));
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        COMBAT_D->do_attack(target,victim,query_temp("weapon", target));
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        COMBAT_D->do_attack(target,victim,query_temp("weapon", target));

        addn_temp("apply/damage", -skill, me);
        addn("neili", -150, me);
        addn_temp("apply/damage", -skill, target);
        addn("neili", -150, target);


        me->start_call_out( (: call_other, __FILE__, "check_fight", me, target, victim, skill/2 :), 1);

        return 1;
}

void check_fight(object me, object target, object victim, int amount)
{
        object weapon;
        if( !query_temp("hebi", me) || !query_temp("hebi", target))return ;

       if( !living(victim) || !present(query("id",victim), environment(me)) || 
                query("qi", victim) <= 50 && me->is_fighting(victim) && target->is_fighting(victim) )
        {
                remove_effect(me, amount);
                remove_effect(target, amount);
                message_vision(HIY"$N��$n�������У�����һЦ��\n\n"NOR, me, target);
                                return;
        }
        else if( (!present(query("id", victim),environment(me)) && target->is_fighting(victim) )
         || (!present(query("id", target),environment(me)) && me->is_fighting(victim))){
                remove_effect(me, amount);
                remove_effect(target, amount);
                tell_object(me, HIR"˫�������Ȼ�߽⣡\n"NOR);
                tell_object(target, HIR"˫�������Ȼ�߽⣡\n"NOR);
                tell_object(victim, HIY"˫�������Ȼ�߽⣬ѹ���ټ����㲻��Ȼ������һ������\n"NOR);
                                return;
        }
         else if( !present(query("id", target),environment(me) )
        || !target->is_fighting() || !me->is_fighting() || !living(target)
        || !living(me) || target->is_ghost() || me->is_ghost() ) {
                remove_effect(me, amount);
        remove_effect(target, amount);
                tell_object(me, HIR"˫�������Ȼ�߽⣡\n"NOR);
                tell_object(target, HIR"˫�������Ȼ�߽⣡\n"NOR);
                tell_object(victim, HIY"˫�������Ȼ�߽⣬ѹ���ټ����㲻��Ȼ������һ������\n"NOR);
                                return;
        }
        else if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"){
                remove_effect(me, amount);
                remove_effect(target, amount);
                tell_object(me, HIR"˫�������Ȼ�߽⣡\n"NOR);
                tell_object(target, HIR"˫�������Ȼ�߽⣡\n"NOR);
                tell_object(victim, HIY"˫�������Ȼ�߽⣬ѹ���ټ����㲻��Ȼ������һ������\n"NOR);
                                return;
        }
        else if( !objectp(weapon=query_temp("weapon", target) )
         || query("skill_type", weapon) != "sword"){
                remove_effect(me, amount);
                remove_effect(target, amount);
                tell_object(me, HIR"˫�������Ȼ�߽⣡\n"NOR);
                tell_object(target, HIR"˫�������Ȼ�߽⣡\n"NOR);
                tell_object(victim, HIY"˫�������Ȼ�߽⣬ѹ���ټ����㲻��Ȼ������һ������\n"NOR);
                                return;
        }
        else if( me->query_skill_mapped("sword") != "quanzhen-jian")
        {
                remove_effect(me, amount);
                remove_effect(target,amount);
                message_vision(HIR"$N"HIR"ͻȻ����һת������ʹ��ȫ�潣����˫���������߽⡣\n"NOR,me);
                return;
        }
        else if( target->query_skill_mapped("sword") != "yunv-jian")
        {
                remove_effect(me, amount);
                remove_effect(target,amount);
                message_vision(HIR"$N"HIR"ͻȻ����һת������ʹ����Ů������˫���������߽⡣\n"NOR,target);
                return;
        }
        call_out("check_fight", 1, me, target, victim, amount);
}

private int remove_effect(object me, int amount)
{
        addn_temp("apply/attack", -amount, me);
        addn_temp("apply/damage", -amount*2, me);
        addn_temp("apply/parry", -amount, me);
        addn_temp("apply/dodge", -amount, me);
        delete_temp("hebi", me);

        return 0;
}
