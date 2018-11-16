//sanzhao.c ����������

#include <combat.h>
#include <ansi.h>

inherit F_SSERVER;

string name() { return "����������"; }

string *limbs =
({
        "ͷ��", "����", "�ؿ�", "����", "���", "�Ҽ�", "���",
        "�ұ�", "����", "����", "����", "����", "����", "С��",
        "����", "����", "����", "���", "�ҽ�", "���", "�Ҷ�"
});
void chkpfm(object me, object target, int amount);
void remove_effect(object me, object target, int amount);
int perform(object me, object target)
{
        object weapon, weapon1;
        int lvl1, lvl2, amount;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!living(target))
                return notify_fail("���Ѿ��ε��ˣ���������׵�ɱ������\n");

        if( time()-query_temp("sxj-t", target)<30 )
                return notify_fail("���Ѿ���Ӧ�������ʽ��������˵�Ѿ���Ч�ˣ�\n");

        if( me->query_skill_mapped("force") != "shenlong-xinfa" &&
            me->query_skill_mapped("force") != "busi-shenlong" )
                return notify_fail("�����õĲ��������ķ����޷�ʩչ���������У�\n");

        if (me->query_skill_mapped("strike") != "yingxiong-sanzhao")
                return notify_fail("��û�м���Ӣ�����У�����ʩչ���������С�\n");

        if (me->query_skill_prepared("strike") != "yingxiong-sanzhao")
                return notify_fail("��û��׼��Ӣ�����У�����ʩչ���������С�\n");

        if( (lvl1=me->query_skill("shenlong-xinfa", 1)) < 150 &&
            me->query_skill("busi-shenlong",1)< 150)
                return notify_fail("��������ķ����δ�����޷�ʩչ���������У�\n");

        if( (lvl2=me->query_skill("strike")) < 200 )
                return notify_fail("��Ӣ��������Ϊ���㣬������ʹ�ö��������У�\n");

        if( (lvl2 - lvl1) < lvl2 / 4 && lvl1 < 200)
                return notify_fail("������������Ҫ����տ�����գ�\n");

        amount = (lvl1+lvl2) / 5;

        if ( amount < 60 ) amount = 60;
        if ( amount > 200 ) amount = 200;

        if( query("neili", me) <= amount*10 )
                return notify_fail("�����������ʹ�ö��������У�\n");

        if( query("jingli", me) <= amount*5 )
                return notify_fail("��ľ�������ʹ�ö��������У�\n");

        if( !query_temp("sanxianjian", me)){
                addn_temp("apply/unarmed_damage", amount*2, me);
                addn_temp("apply/attack", amount, me);
                addn_temp("apply/dodge", amount, me);
                set_temp("sanxianjian", 1, me);
                me->start_busy(1);
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me, target, amount:), amount/15);
        }

        message_combatd(HIW "$nץס$N�ĺ󾱣�һ������$N����������ת����$n��Ҹ��ɦ��һ�ѣ�\n$n��������������$N������ס$nҸ�£�����������ת��ץס$n��ڣ�����\n����$n�����ӣ������Լ�ͷ��������ˤ����\n"NOR, me, target);
        chkpfm(me, target, amount);
        message_combatd(HIW "$N�������ϣ�$n������̤ס$N�ĺ�����$N˫��һ����������ݣ�\n�ұ�ȴ�������Ӷ�����ͻȻ��һ�������$n�Ŀ�����ȥ��ֻһ����\n������ץס$n�ҽ����ף�������$nС����ȥ��\n"NOR, me, target);
        chkpfm(me, target, amount);
        set_temp("sxj-c", 3, me);
        message_combatd(HIW"$N˫�۷��ڱ���ͻȻ˫��ʮָ���𣬸��ɰ���֮�Σ��������һײ\nʮָ��ץ��$n���ز���$n���һ����$NͻȻһ�������������Ծ��\n˫��һ�֣��ѿ���$n��ͷ��ͬʱ˫�ְ�ָѹס$n̫��Ѩ��ʳָ��ü����ָ���ۣ�\n"NOR, me, target);
        chkpfm(me, target, amount);



        if( query("eff_qi", target)*100/query("max_qi", target) <= 20
          && query("qi", target)*100/query("max_qi", target) <= 5
          && query_temp("sxj-c", me) == 3 )
        {
                message_combatd(HIR "\n$N"+HIR+"�����ھ���ע������ǿ��֮����$n���类��շ������ش�ɨ�����������һ����Ѫ����\n" NOR, me, target);
                target->die(me);
        }

        me->start_busy(2);
        return 1;
}
void chkpfm(object me, object target, int amount)
{
        object weapon2=query_temp("weapon", target);
        string attack_skill, dodge_skill, parry_skill, result, msg = "";
        int ap, dp, pp, damage, level;

        if( !me->is_fighting(target) || !living(target) )
                return;

        level = me->query_skill("yingxiong-sanzhao", 1);
        damage = amount+random(level)/2;
        ap = COMBAT_D->skill_power(me, "strike", SKILL_USAGE_ATTACK)/ 100;
        if( ap < 1) ap = 1;

        dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE)/ 100;
        if( target->is_busy() ) dp /= 3;
        if( dp < 1 ) dp = 1;
        if( random(ap + dp) < dp )
        {
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg();
        }
        else
        {
                pp = COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE)/100;
                if( target->is_busy() ) pp /= 2;
                if( pp < 1 ) pp = 1;

                if( random(ap + pp) < pp )
                {
                        parry_skill = target->query_skill_mapped("parry");
                        if( !parry_skill || !SKILL_D(parry_skill)->parry_available())
                                parry_skill = "parry";
                        msg += SKILL_D(parry_skill)->query_parry_msg(weapon2, target);
                }
                else
                {
                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage/3, me);
                        if( query_temp("sxj-c", me) == 3 )
                                result = COMBAT_D->damage_msg(damage, "����");
                        else result = COMBAT_D->damage_msg(damage, "����");
                        msg += result;
                        result=COMBAT_D->status_msg(query("qi", target)*100/
                                query("max_qi", target));
                        msg += "( $n"+result+" )\n";
                        target->start_busy(1);
                }
        }
        result = limbs[random(sizeof(limbs))];
        msg = replace_string( msg, "$l", result );
        message_combatd(msg, me, target);
}
void remove_effect(object me, object target, int amount)
{
        if (!me) return;
        delete_temp("sanxianjian", me);
        if( me->is_fighting() && living(target))
        {
                message_combatd(HIY "\n$n��������Ӧ��$P���������е�������\n" NOR, me, target);
                set_temp("sxj-t", time(), target);
        }
        else message_combatd(HIY "\n$N�ջ��ھ�,��ʽҲ�ָ���ƽ����\n" NOR, me);
        addn_temp("apply/unarmed_damage", -amount*2, me);
        addn_temp("apply/attack", -amount, me);
        addn_temp("apply/dodge", -amount, me);
}
