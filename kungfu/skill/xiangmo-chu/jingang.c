// This program is a part of NT MudLIB
// xiangmo.c ��ս�ħ

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "��ս�ħ"; }

int perform(object me, object target)
{
        object weapon;
        int lxbr,nec,damage,amount,quick,ap,dp;
string str = @TEXT
                                                |\
                .-':'"": - -   -  -   : -  \ (1\.`-.
              .'`.  `.  :  :  :   :   : : : : : :  .';
             :-`. :   .  : :  `.  :   : :.   : :`.`.o ;
             : ;-. `-.-._.  :  :   :  ::. .' `. `., =  ;
             :-:.` .-. _-.,  :  :  : ::,.'.-' ;-. ,'''"
           .'.' ;`. .-' `-.:  :  : : :;.-'.-.'   `-'
    :.   .'.'.-' .'`-.' -._;..:---'''"~;._.-;
    :`--'.'  : :'     ;`-.;            :.`.-'`.
     `'"`    : :      ;`.;             :=; `.-'`.
             : '.    :  ;              :-:   `._-`.
              `'"'    `. `.            `--'     `._;
                        ''''
TEXT;
        if (!target) target = offensive_target(me);
        if (!target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("����ս�ħ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        weapon=query_temp("weapon", me);
        if( !objectp(weapon) || query("skill_type", weapon) != "hammer" )
                return notify_fail("���������ƣ���ν�ħ��\n");

        if (me->query_skill("longxiang", 1) < 150 && me->query_skill("mizong-neigong",1) < 150 )
                return notify_fail("����ڹ����δ�����޷�ʩչ��ħ������\n");

        if (me->query_skill("xiangmo-chu", 1) < 150)
                return notify_fail("��Ľ�ħ�ƻ��δ�����޷�ʩչ��ħ������\n");

        if (me->query_skill("necromancy",1) < 200)
                return notify_fail("�㽵������Ϊ��������ν������ˣ�\n");

        if( query("neili", me) <= 1000 )
                return notify_fail("�����������ʹ�á���ս�ħ����\n");

        if( query("jingli", me) <= 500 )
                return notify_fail("��ľ�������ʹ�á���ս�ħ����\n");

        if( query_temp("xiangmo_busy", me) )
                return notify_fail("������ʹ�ý����󷨣�ȴ��ôҲʹ��������\n");

        if( target->is_busy() )
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        nec = me->query_skill("necromancy",1);
        quick = (int)(me->query_skill("longxiang",1)/100);
        if (quick < 2) quick = 2;
        amount = (int)me->query_skill("hammer")/4;
        if (amount < 60) amount = 60;
        if (amount > 100) amount = 100;
        addn_temp("apply/damage", amount, me);
        addn_temp("apply/attack", amount*2, me);
        set_temp("xiangmo_busy", 1, me);
        message_combatd(HIR"\n$N�����ս���������ڲ����������ԣ�ʹ������ս�ħ���󷨡�\n"NOR,me,target);
        message_combatd("$Nһ���ߺ������ζ�ת������ѩ����ɽ��\n",me,target);
        message_combatd(HIW+str+NOR,me,target);
        ap = nec + attack_power(me, "hammer");
        dp = defense_power(target, "force");

        if(random(ap)>dp/2 || !living(target))
        {
                damage=damage_power(me, "hammer");
                if (damage<500) damage=500;
                if( query("id", weapon) == "xiangmo chu")damage*=3/2;
                if (random(ap)>dp/2 || !living(target))
                {
                        message_combatd(HIR"\n$n�����龰���Ѳ�֪���룬ֻ��ͷ���ۻ�����ȫ��$N������\n"NOR, me,target);
                        target->receive_wound("qi", damage/3 + random(damage/3), me);
                        target->receive_wound("jing", damage/5 + random(damage/3), me);
                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_combatd("($N"+str+")\n", target);
                        if( !target->is_busy() )
                                target->start_busy(2);
                }
                else
                {       message_combatd(HIR"\n$n�����龰���������ѣ����������Ĳ�����$N�Ľ�ħ��Ӱ��\n"NOR,me,target);
                        target->receive_damage("jing", damage/5 + random(damage/3), me);
                        target->receive_wound("qi", damage/4 + random(damage/3), me);
                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_combatd("($N"+str+")\n", target);
                        if( !target->is_busy() )
                                target->start_busy(1+random(3));
                        message_combatd(HIR"\n$N��$n©���������߾�����"+query("name", weapon)+HIR"��$nϮ����\n"NOR,me,target);
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
                }
                me->start_busy(3);
        }
        else
        {
                message_combatd(HIR"$n�����龰��ڤ˼һ��������ʶ����$N�Ľ�ħ��Ӱ��\n"NOR, me, target);
                message_combatd("ֻ��$n���˷���������Ʈ�磬������$N�������,$N��ʱ��֪���롣\n",me,target);
                me->start_busy(4);
        }
        addn_temp("apply/damage", -amount, me);
        addn_temp("apply/attack", -amount*2, me);
        addn("neili", -query("jiali", me)-500, me);
        addn("jingli", -query("jiajin", me)-400, me);
        call_out("remove_effect", random(9-quick), me);
        return 1;
}
void remove_effect(object me)
{
        if (!me) return;
        delete_temp("xiangmo_busy", me);
        tell_object(me, HIY"\n���ϢƬ�̣��������ֿ��շ������ˡ�\n"NOR);
}
