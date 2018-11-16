//lianhuan.c  ��ħ�ȷ�֮��ħ����

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

void check_fight(object me, object target, object weapon);
private int remove_attack(object me, object weapon);

int perform(object me, object target)
{
        object weapon;
        int skill;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��ħ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("fengmo", me) )
                return notify_fail("������ʹ�÷�ħ�����ˣ�\n");

        weapon=query_temp("weapon", me);
        if( !objectp(weapon) || query("skill_type", weapon) != "staff" )
                return notify_fail("���������ȣ�����ܹ�ʩչ��ħ���ȣ�\n");

        if( me->query_skill_mapped("force") != "huntian-qigong" && me->query_skill_mapped("force") != "jiaohua-neigong"  )
                return notify_fail("�����õ��ڹ����ԣ��޷�����ȷ�ʩչ��ħ���ȣ�\n");

        if( me->query_skill("force") < 100 )
                return notify_fail("����ڹ����δ�����޷�����ȷ�ʩչ��ħ���ȣ�\n");

        if( me->query_skill("staff") < 100 )
                return notify_fail("���ħ�ȷ���Ϊ���㣬������ʹ�÷�ħ���ȣ�\n");

        if( query("neili", me) <= 300 )
                return notify_fail("�����������ʩչ��ħ���ȣ�\n");
        if( query("jingli", me) <= 200 )
                return notify_fail("��ľ�������ʩչ��ħ���ȣ�\n");

        skill = me->query_skill("staff");
        
        message_vision(HIR "\n$N���һ�������м�ת�ŵ�"+weapon->name()+"�����������ڿ��иߵ����һ�����\n\n" NOR, me, target);

        set_temp("fengmo", 1, me);
        set_temp("location", file_name(environment(me)), me);
        addn("neili", -200, me);
        addn("jingli", -100, me);
        weapon->unequip();
        set("no_clean_up", 1, weapon);
        me->reset_action();
        call_out("check_fight", 1, me, target, weapon);

        return 1;
}

void check_fight(object me, object target, object weapon)
{
        string *limbs, limb, result, str, type;
        int damage, dp;

        if ( !objectp( me ) ) return;
        me->reset_action();

        if( query_temp("fengmo", me) >= me->query_skill("fengmo-zhang",1)/5 || 
             !living(me) ||
             !me->is_fight(target) ||
             !query_temp("fengmo", me) )
        {
               call_out("remove_attack", 1, me, weapon);
        } else {
                limbs=query("limbs", target);
                limb = limbs[random(sizeof(limbs))];
                type = "����";

                message_vision(HIR "\nͻȻ��$n������$N��"+limb+"��Ȼ��ײ��ȥ��\n" NOR, target, weapon);

                if (living(target))
                        dp=query("combat_exp", target);
                else  dp = 0;
                if( random(query("combat_exp", me))>dp )
                {
                        //RYU: the following code is to make it look nice.
                        damage = 5+random(me->query_skill("fengmo-zhang", 1));
                        target->receive_damage("qi", damage, me);

                        result = COMBAT_D->damage_msg(damage, type);
                        result = replace_string( result, "$l", limb);
                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));

                        message_vision(result, me, target);
                        message_vision("($N"+str+")\n", target);

                } else {
                        message_vision(YEL "$N���÷���������һ�ã��ܹ���$n��\n" NOR, target, weapon);
                }
        
                message_vision(HIR "\n$N����һ������Ʈ�����$n��������βһ�ƣ����������ڰ�շ�����\n\n" NOR, me, weapon);

                addn_temp("fengmo", 1, me);
                call_out("check_fight", 1, me, target, weapon);
        }
}               

int remove_attack(object me, object weapon)
{
        if ( !objectp( me ) ) return 1;
        if( !query_temp("fengmo", me))return 1;
        delete_temp("fengmo", me);
        
        if( file_name(environment(me)) == query_temp("location", me) && living(me)){
                weapon->move(me);
                set("no_clean_up", 0, weapon);
                weapon->wield();
                message_vision(YEL "\n$N������ǰ����������$n�ջء�\n\n" NOR, me, weapon);
        }
        else {
                weapon->move(query_temp("location", me));
                message("vision", "ֻ�����ϵ�һ����"+weapon->name()+"�����ɰ�յ��䡣\n", environment(weapon), ({weapon}) );
        }
        delete_temp("location", me);

        return 1;
}