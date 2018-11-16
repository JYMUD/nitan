// This program is a part of NITAN MudLIB
// hun.c ����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIM "����" NOR; }

int can_not_hubo() { return 1;}

void check_fight(object me, object target, object weapon);
private int remove_attack(object me, object weapon);

int perform(object me, object target)
{
        string msg;
        object *ob, weapon;
        int ap, dp, count, p;
        int i, damage;

        if( !query("reborn/times", me) )
                return notify_fail("����δת���������޷�ʩչ" + name() + "��\n");

        if( query("family/family_name", me) != "��ɽ��"
         && member_array("��ɽ��", query("reborn/fams", me)) == -1 )
                return notify_fail("����δת���������޷�ʩչ" + name() + "��\n");

/*
        if( query("family/family_name", me) != "��ɽ��" )
                return notify_fail("�㲻�ǻ�ɽ�ɵ��ӣ��޷�ʩչ" + name() + "��\n");
*/
        /*
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail(HUN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        */

        if( !me->is_fighting() )
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("dugu_jianhun", me) )
                return notify_fail("������ʹ��" + name() + "�ˣ�\n");

        weapon=query_temp("weapon", me);
        if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
                return notify_fail("�������޽�������ܹ�ʩչ" + name() + "��\n");

        if( (int)me->query_skill("lonely-sword", 1) < 1000 )
                return notify_fail("��Ķ��¾Ž�������죬����ʩչ" + name() + "��\n");

        if( me->query_skill("force") < 1200 )
                return notify_fail("����ڹ����δ�����޷�����ȷ�ʩչ" + name() + "��\n");

        if( me->query_skill("sword", 1) < 1000 )
                return notify_fail("�㽣����Ϊ���㣬������ʹ��" + name() + "��\n");

        if( me->query_skill("sword-cognize", 1) < 500 )
                return notify_fail("�㽣���������δ����������ʹ��" + name() + "��\n");

        if( me->query_skill("martial-cognize", 1) < 500 )
                return notify_fail("����ѧ�������δ����������ʹ��" + name() + "��\n");

        if( query("neili", me) <= 1000 )
                return notify_fail("�����������ʩչ" + name() + "��\n");

        if( query("jingli", me) <= 500 )
                return notify_fail("��ľ�������ʩչ" + name() + "��\n");

        count = me->query_skill("sword-cognize", 1) + me->query_skill("martial-cognize", 1);
        count /= 500;

        msg = HIW "$N" HIW "��̬д�⣬���ḧŪ���е�" + weapon->name() + HIW "��ֻ��" + weapon->name() +
              HIW "�����ӹ�һ˿��Ӱ��΢΢���������ѽ����鶯�������������\n" NOR
              HIM"$N"HIM"������"+query("name", weapon)+HIM"�����̳��������������£�\n"NOR
              HIM "���п��ƻ�������ʵ�������磬�����������£�ȴ�Ǻ�" + weapon->name() + HIM "��Ϊһ�壬��и�ɻ����̺��ŷ�豹�����⾳��\n" NOR;

        message_combatd(msg, me);

        damage = damage_power(me, "sword");
        damage += query_temp("apply/damage", me);
        damage += query("jiali", me);
        damage *= 5;
        ap = attack_power(me, "sword") +
             me->query_skill("dodge");

        ob = me->query_enemy();
        addn_temp("apply/ap_power", 100, me);
        for (i = 0; i < sizeof(ob); i++)
        {
                dp = defense_power(ob[i], "parry") +
                     ob[i]->query_skill("dodge");

                if (ap * 2 / 3 + random(ap) > dp)
                {
                        ob[i]->receive_damage("qi", damage, me);
                        ob[i]->receive_wound("qi", damage / 2, me);
                        ob[i]->set_weak(5);
                        set("neili", 0, ob[i]);
                        set("jiali", 0, ob[i]);
                        ob[i]->apply_condition("no_exert", 10);
                        ob[i]->apply_condition("no_perform", 10);

                        msg = HIR "$n" HIR "���м�ȴ���޴��мܣ�����Ҳ�е��޴��ɶ㣬��ʱ��$N" HIR "һ��������\n"
                              HIR "�����ش���һ��׶�ĵĴ�ʹ��ȫ������ԴԴ��к��\n" NOR;

                        if( query_temp("apply/fatal_blow", me) && query("ability2/fatal_blow", me) )
                        {
                                if( random(100) < query("ability2/fatal_chance", me) )
                                {
                                        ob[i]->receive_damage("qi", query("qi", ob[i]) * query_temp("apply/fatal_blow", me)/100, me);
                                        ob[i]->receive_wound("qi", query("qi", ob[i]) * query_temp("apply/fatal_blow", me)/200, me);
                                        msg += HIR "�����ţ�$N" HIR "׷��������һ������$n" HIR "��ɸ����صĴ��ˡ�\n" NOR;
                                }
                        }
                        p=query("qi", ob[i])*100/query("max_qi", ob[i]);
                        msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                        message_vision(msg, me, ob[i]);
                } else
                {
                        ob[i]->start_busy(2);
                        msg = HIC "$n" HIC "�鼱֮�£��������ǣ�����һ�������ұܿ�$N" HIC "��һ�еĹ������亹ֱ�ܣ�\n" NOR;
                        message_vision(msg, me, ob[i]);
                }
        } ;
        addn_temp("apply/ap_power", -100, me);
        me->start_busy(2);
        set_temp("dugu_jianhun", 1, me);
        addn("neili", -200, me);
        addn("jingli", -100, me);

        msg = HIY "$N" HIY "�ս�" + weapon->name() + HIY "����һָ, �е� : ����һ�� �� Ѫ������ �� \n"
              HIY "��ʱ" + weapon->name() + HIY "������һ����ɫ�Ľ��Σ������������������ ...\n" NOR;

        message_combatd(msg, me);
        call_out("check_fight", 1, me, weapon, count);

        return 1;
}

void check_fight(object me, object weapon, int count)
{
        object *ob;
        int damage, ap, dp, p;
        string msg, limb;
        string *limbs;
        int i;

        if( !objectp( me ) || !objectp(weapon) ) return;

        if( query_temp("dugu_jianhun", me) >= count
        ||      !me->is_fighting() )
        {
                call_out("remove_attack", 1, me, weapon);
                return;
        }

        addn_temp("dugu_jianhun", 1, me);
        message_combatd(HIR "\n�����������ĸ����ڿ��д���, �Կ����ޱȵ����龡����� ...\n" NOR, me);

        ob = me->query_enemy();
        ap = me->query_skill("sword", 1) + me->query_skill("sword-cognize", 1) +
             me->query_skill("martial-cognize", 1);
        damage=ap+query("weapon_prop/damage", weapon);
        damage += damage_power(me, "sword");
        damage *= 5;

        for (i = 0; i < sizeof(ob); i++)
        {
                if (! objectp(ob[i])) continue;
                dp=query("parry", ob[i])+
                     ob[i]->query_skill("dodge", 1);

                if (dp / 3 + random(dp) < ap)
                {
                        limbs=query("limbs", ob[i]);
                        if (! arrayp(limbs))
                        {
                                limbs = ({ "����" });
                                set("limbs", limbs, ob[i]);
                        }
                        limb = limbs[random(sizeof(limbs))];
                        ob[i]->start_busy(1);
                        ob[i]->receive_damage("qi", damage, me);
                        ob[i]->receive_wound("qi", damage / 2, me);
                        p=query("qi", ob[i])*100/query("max_qi", ob[i]);
                        msg = COMBAT_D->damage_msg(damage, "����");
                        msg = replace_string(msg, "$l", limb);
                        msg = replace_string(msg, "$w", weapon->name());
                        msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                        message_combatd(msg, me, ob[i]);
                }
        }

        call_out("check_fight", 1, me, weapon, count);
}

int remove_attack(object me, object weapon)
{
        if( !objectp( me ) ) return 1;
        if( !query_temp("dugu_jianhun", me))return 1;

        delete_temp("dugu_jianhun", me);
        message_combatd(HIW "һ�����֮��, �������Զ������������" + weapon->name() + HIW " ...\n" NOR, me);

        return 1;
}
