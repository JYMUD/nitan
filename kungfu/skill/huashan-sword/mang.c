// This program is a part of NITAN MudLIB
// mang.c ��â


#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "��â"; }
string *name1 = ({
        "����Ѩ",
        "���Ѩ",
        "����Ѩ",
        "����Ѩ",
        "����Ѩ",
        "�Ϲ�Ѩ",
        "���Ѩ",
        "�ٻ�Ѩ",
        "̫��Ѩ",
        "��ǿѨ",
        "��̨Ѩ"
});

void check_fight(object me, object target, int amount);

int perform(object me, object target)
{
        string msg, name, name2;
        int ap, dp;
        object weapon=query_temp("weapon", me);

        if (! target) target = offensive_target(me);

        if (! target || ! target->is_fighting(me))
                return notify_fail("����â��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query("qi", target) <= 50 )
                return notify_fail("������û�б�Ҫ�á���â�����������ˡ�\n");

        if( !weapon || query("skill_type", weapon) != "sword"
        ||  me->query_skill_mapped("sword") != "huashan-sword")
                return notify_fail("�������޷�ʹ�á���â���������ˡ�\n");

        if( query_temp("perform", me) == 1 ||
            query_temp("perform2", me) == 1 ||
            query_temp("perform3", me) == 1 )
                return notify_fail("�����������š���â���ء�\n");

        if ((int)me->query_skill("huashan-sword", 1) < 100 ||
            (int)me->query_skill("sword", 1) < 100 ||
            (int)me->query_str() < 25   ||
            (int)me->query_dex() < 25)
                return notify_fail("���еĹ��򻹲�����죬����ʹ�á���â����\n");

        if ((int)me->query_skill("zixia-shengong", 1) < 80)
                return notify_fail("�����ϼ����Ϊ�������޷����򡸽�â���ľ��衣\n");


        if( query("max_neili", me)<800 )
                return notify_fail("�������̫�����޷�ʹ�ó�����â����\n");

        if( query("neili", me)<200 )
                return notify_fail("�������������\n");

        name = name1[random(sizeof(name1))];
        name2=query("name", weapon);

        msg = HIC "\n$N���ֽ���һת������" + name2 + HIC "ֱ������ʱʹ$N" +
              HIC "��һƬ���������֣�����һ֧��â����$n " HIC "��" + name + "��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "���һ�����У�$nֻ����ȫ������ͨ���������������ܸ��ӣ�\n"NOR;
                if (! target->is_busy())
                        target->start_busy(2 + random(4));
                addn("neili", -200, me);
                set_temp("perform", 1, me);

                if ((int)me->query_skill("huashan-sword", 1) > 120
                && query("neili", me)>300 )
                {
                        call_out("perform2", 0, me , target);
                } else
                {
                        delete_temp("perform", me);
                }
        } else
        {
                me->start_busy(2);
                addn("neili", -100, me);
                addn("neili", -100, target);
                msg += HIY"\n$p���һ�����ã�ȫ������һ�ݣ�˳�����˿�ȥ��\n" NOR;
        }
        message_combatd(msg, me, target);
        me->start_call_out((: call_other, __FILE__, "check_fight",
                           me ,target :), 1);
        return 1;
}

int perform2(object me, object target)
{
        string msg, name, name2;
        int damage, ap, dp;
        object weapon;

        if (! me) return 0;
        weapon=query_temp("weapon", me);

        if (! weapon)
        {
                me->start_call_out((: call_other, __FILE__, "check_fight",
                                   me ,target :), 1);
                return 1;
        }
        name2=query("name", weapon);

        if (! target) target = offensive_target(me);
        if (! target)
        {
                call_out("back", 3, me);
                return 1;
        }

        name = name1[random(sizeof(name1))];
        msg = MAG "\n����$N̤ǰһ����" + name2 + "�����ĵڶ�֧��â���յ���$n��" + name + "����Ѩ�������֮�\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                delete_temp("perform", me);
                damage = damage_power(me, "sword");

                addn("neili", -300, me);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "���ֻ����$n" HIR "һ���Һ���" + name2 + HIR "����$p��" + name +
                                           HIR "�Դ���������Ѫ�������أ���\n" NOR);

                if( !target->is_busy() )
                        target->start_busy(2);

                if ((int)me->query_skill("huashan-sword", 1) > 140
                && query("neili", me)>300 )
                {
                        call_out("perform3", 0, me ,target);
                } else
                {
                        delete_temp("perform2", me);
                }
        } else
        {       me->start_busy(3);
                addn("neili", -100, me);
                delete_temp("perform", me);
                msg += HIY"����$pһ�����Ʒ���ԶԶ�Ķ��˿�ȥ��\n"NOR;
        }
        message_combatd(msg, me, target);
        me->start_call_out( (: call_other, __FILE__, "check_fight", me ,target :), 1);
        return 1;
}

int perform3(object me, object target)
{
        int skill, j, ap, dp;
        string msg, name, name2;
        object weapon;

        if( !me || !weapon=query_temp("weapon", me) )
        {
                me->start_call_out( (: call_other, __FILE__, "check_fight", me ,target :), 1);
                return 1;
        }
        name2=query("name", weapon);
        skill = (int)me->query_skill("huashan-sword", 1);
        skill = skill / 15;

        if (! target) target = offensive_target(me);
        if (! target)
        {
                call_out("back", 3, me);
                return 1;
        }

        name = name1[random(sizeof(name1))];
        msg = HIW "\n������$N����" + name2 + "��������֧��â��ֻ��һ����âֱ��$n������ɨ��$n��" + name + "��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                delete_temp("perform2", me);

                msg += HIR "$nֻ�������澭��������ϢΪ֮һ����ȫ��������Ȼ�᲻�����ˣ�\n" NOR;
                msg += HIW "$N��$n����һ���ĵ��������������������������ǽ��ھ���" + HIR "���������ɽ�����\n" NOR;
                message_combatd(msg, me, target);
                addn("apply/attack", skill, me);
                addn("apply/damage", skill, me);

                for(j=0;j<(3+query("str", me)/10);j++ )
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);

                addn("apply/attack", -skill, me);
                addn("apply/damage", -skill, me);

                if( !target->is_busy() )
                        target->start_busy(4);
                me->start_busy(3);
                addn("neili", -500, target);
                call_out("back", 3 + skill, me);

        } else
        {
                me->start_busy(3);
                addn("neili", -100, me);
                delete_temp("perform2", me);
                target->start_busy(1);
                msg += HIY"\n$p��Ϣδ������$P���з����Ľ�â������������æ��Ծ�����ߣ��Ǳ��رܿ���\n" NOR;
                message_combatd(msg, me, target);
        }
        me->start_call_out( (: call_other, __FILE__, "check_fight", me ,target :), 1);
        return 1;
}

void back(object me)
{
        string msg;
        if (! me) return;
        msg = HIW "\n������һ�գ����н�â������ʧ��\n" NOR;
        tell_object(me, msg);
        delete_temp("perform", me);
        delete_temp("perform2", me);
        delete_temp("perform3", me);
}

void check_fight(object me, object target, int amount)
{
        object weapon, where;
        if ( target )
        {
                where = environment(target);
                if ( !present(target,where) )
                {
                        if( query("qi", target) <= 50 && me->is_fighting(target) )
                        {
                                delete_temp("perform", me);
                                delete_temp("perform2", me);
                                remove_call_out("perform2");
                                remove_call_out("perform3");
                        }
                        else
                        if( !objectp(weapon=query_temp("weapon", me) )
                         || query("skill_type", weapon) != "sword"
                        || me->query_skill_mapped("sword") != "huashan-sword")
                        {
                                remove_call_out("perform2");
                                remove_call_out("perform3");
                                delete_temp("perform", me);
                                delete_temp("perform2", me);
                        }
                        else
                        if( !present(query("id", target),environment(me) )
                        || !target->is_fighting() || !me->is_fighting() || !living(target)
                        || !living(me) || target->is_ghost() || me->is_ghost() )
                        {
                                delete_temp("perform", me);
                                delete_temp("perform2", me);
                                remove_call_out("perform2");
                                remove_call_out("perform3");
                        }
                        else call_out("check_fight", 1, me, target, amount);
                } else
                {
                        delete_temp("perform", me);
                        delete_temp("perform2", me);
                        delete_temp("perform3", me);
                }
        }

}

