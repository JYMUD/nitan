// This program is a part of NITAN MudLIB
// ������ӿ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "������ӿ"; }

string *xue_name = ({
        "�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
        "����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
});

int perform(object me, object target)
{
        string msg, dodge_skill;
        int i, j, ap, dp;
        object weapon;

        if( query("gender", me) == "����" )
        {
                i = me->query_skill("xuantie-jian", 1) / 4;
                j = me->query_skill("sword", 1) / 4;
        }
        else
        {
                i = me->query_skill("xuantie-jian", 1) / 5;
                j = me->query_skill("sword", 1) / 5;
        }
        weapon=query_temp("weapon", me);

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���������ġ�������ӿ��ֻ����ս���жԶ���ʹ�á�\n");

        if( !weapon || query("skill_type", weapon) != "sword" )
                return notify_fail("�����ʹ����������ʹ�á�������ӿ����\n");

        if ((int)me->query_skill("xuantie-jian", 1) < 130)
                return notify_fail("�������������������죬ʹ������������ӿ��������\n");

        if ((int)me->query_skill("surge-force", 1) < 130
        &&  (int)me->query_skill("surge-force", 1) < 130)
                return notify_fail("��Ĺ�Ĺ�ڹ��ȼ���������ʹ������������ӿ��������\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("����ڹ��ȼ�����������ʹ�á�������ӿ����\n");

        if ((int)me->query_str() < 33)
                return notify_fail("�������������ǿ����ʹ������������ӿ������\n");

        if( query_temp("xtjf/haichao", target) || target->is_busy() )
                return notify_fail(target->name()+"���Թ˲�Ͼ������Է��ĵؽ�����\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian" && userp(me))
                return notify_fail("�������޷�ʹ�á�������ӿ����\n");

        if (me->query_skill_mapped("parry") != "xuantie-jian" && userp(me))
                return notify_fail("�������޷�ʹ�á�������ӿ����\n");

        if( query("max_neili", me)<(me->query_skill("force")+j+200) )
                return notify_fail("����������̫����ʹ������������ӿ����\n");

        message_combatd(HIB"\n$N��"+query("name", weapon)+
                        HIB "Ю���˳�ӿ֮�ƣ������γ�һ����ת�����У���$n���ֹ�ȥ��\n" NOR,
                        me, target);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                message_combatd(HIR "���$nȫ���������γɵ������������ţ�ֻ�����������ݺ��ξ��ˣ�����ײײ��\n" NOR,
                                me, target);

                if( !target->is_busy() )
                        target->start_busy(2 + ap / 80);
                set_temp("xtjf/haichao", 1, target);
                addn("neili", -i*3, me);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);

                if (me->query_skill("xuantie-jian", 1) > 180)
                {
                        remove_call_out("remove_effect");
                        call_out("remove_effect", 1, me, target);
                }

                if ((int)me->query_skill("xuantie-jian", 1) > 150
                 && query("neili", me)>(me->query_skill("force",1)+j )
                &&  present(target, environment(me))
                &&  me->is_fighting(target))
                {
                        message_combatd(HIB"\n$N΢Ц������ƽ����е�"+query("name", weapon)+
                                        HIB "������죬������ᣬ����Ȼ�����������֮������$nϯ���ȥ��\n" NOR,
                                        me, target);

                        if (random(me->query_skill("sword", 1)) > target->query_skill("parry", 1) / 3
                        ||  ! living(target)
                         || query("level", me)>query("level", target) )
                        {
                                addn_temp("apply/str", i, me);
                                addn_temp("apply/attack", j, me);
                                addn_temp("apply/damage", j, me);
                                set_temp("xtjf_pfm", 1, me);
                                COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
                                COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
                                addn_temp("apply/str", -i, me);
                                addn_temp("apply/attack", -j, me);
                                addn_temp("apply/damage", -j, me);

                                addn("neili", -200, me);
                                delete_temp("xtjf_pfm", me);
                        } else
                        {
                                addn("neili", -100, me);
                                dodge_skill = target->query_skill_mapped("dodge");
                                if (! dodge_skill ) dodge_skill = "dodge";
                                        msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                                message_combatd(msg, me, target);
                        }
                        return 1;
                }
        } else
        {
                me->start_busy(2+random(2));
                addn("neili", -100, me);
                dodge_skill = target->query_skill_mapped("dodge");
                if (! dodge_skill ) dodge_skill = "dodge";
                        msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                message_combatd(msg, me, target);
        }
        return 1;
}

void remove_effect(object me, object target)
{
        remove_call_out("remove_effect");
        if (! me) return;
        if (objectp(target) && ! me->is_fighting(target))
        {
                delete_temp("xtjf", target);
                return;
        }
        if (objectp(target)
        &&  me->is_fighting(target)
        &&  ! target->is_busy()
        &&  random(2) == 1
         && query_temp("weapon", me) )
        {
                delete_temp("xtjf", target);
                call_out("perform2", 1, me, target);
                return;
        }
        call_out("remove_effect", 1 ,me ,target);
}

int perform2(object me, object target)
{
        string msg, dodge_skill,name;
        object weapon=query_temp("weapon", me);
        int p, ap, dp, damage;

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return 0;

        if( !weapon || query("skill_type", weapon) != "sword" )
                return 0;
        if( me->query_skill_mapped("sword") != "xuantie-jian" && userp(me))
                return 0;

        if( me->query_skill_mapped("parry") != "xuantie-jian" && userp(me))
                return 0;

        if( query("neili", me)<1000 )
                return 0;

        if( query("gender", me) == "Ů��" )
                p = me->query_skill("force", 1) / 6;
        else
                p = me->query_skill("force", 1) / 8;

        name = xue_name[random(sizeof(xue_name))];
        msg =HIB"\n$n�ò����׻���������$N����Ʈ����ת�˼�ת���Ʋ�����������һ������$n��"RED+name+HIB"��\n"NOR;

        ap=attack_power(me, "sword");
        dp=defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += CYN"$n�پ���ǰһ���Ի�һʱ���������ϵ�"RED+name+CYN"�ѱ�"+weapon->name()+CYN"���С�\n"NOR;
                addn_temp("apply/attack", -p/2, target);
                addn_temp("apply/defense", -p/2, target);
                target->set_temp("xtjf/haichao");
                target->receive_damage("qi", damage,  me);
                target->receive_wound("qi", random(damage/2)+damage/2, me);
                if( random(2) == 1)
                {
                        target->apply_condition("no_perform", 1+ random(2));
                        target->set_temp("xtjf/perform");
                }
                else
                {
                        target->apply_condition("no_exert", 1+random(2));
                        target->set_temp("xtjf/exert");
                }
                addn("neili", -p*6, me);
                call_out("check_fight", 1, me, target, weapon, p );
        }
        else {
                me->start_busy(2+random(2));
                addn("neili", -100, me);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                        msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_combatd(msg, me, target);
        return 1;
}

void check_fight(object me,object target,object weapon, int p)
{
        remove_call_out("check_fight");
        if( !target) return;
        if( ! me
         || ! me->is_fighting("target")
          || !query_temp("weapon", me )
          || query("skill_type", weapon) != "sword"
         || ! present(target,environment(me))
         || me->query_skill_mapped("sword") != "xuantie-jian"){
                addn_temp("apply/attack", p/2, target);
                addn_temp("apply/defense", p/2, target);
                if( query_temp("xtjf/perform", target) )
                        target->clear_condition("no_perform");
                if( query_temp("xtjf/exert", target) )
                        target->clear_condition("no_exert");
                delete_temp("xtjf", target);
                message_combatd(HIW"\n$N���������˾��������λָ���ԭ�ȵĽýݡ�\n"NOR, target);
                return ;
        }
        call_out("check_fight", 1, me, target, weapon, p );
}
