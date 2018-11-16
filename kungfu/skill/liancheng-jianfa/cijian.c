// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

string name() { return "�̼�ʽ"; }

string *limbs = ({
        "ͷ��", "����", "�ؿ�", "����", "���", "�Ҽ�", "���",
        "�ұ�", "����", "����", "����", "С��", "����", "����",
        "���", "�ҽ�", "���", "�Ҷ�", "����", "����",
});

void remove_effect(object target);
string *songs = ({"HIC", "HIR", "HIW", "HIY"});

int perform(object me, object target)
{

        int damage, p, ap, dp;
        object weapon;
        string msg, song, dodge_skill;

        song = songs[random(sizeof(songs))];

        if( !target ) target = offensive_target(me);

        weapon=query_temp("weapon", me);
        if( !target )
                target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("��"HIM"�̼�ʽ"NOR"��ֻ����ս���жԶ���ʹ�á�\n");

        if (!weapon
                 || query("skill_type", weapon) != "sword"
                || me->query_skill_mapped("sword") != "liancheng-jianfa")
                return notify_fail("������û�н����޷�ʹ�á�"HIM"�̼�ʽ"NOR"����\n");

        if( (int)me->query_skill("liancheng-jianfa",1) < 150 )
                return notify_fail("������ǽ���������죬����ʹ�á�"HIM"�̼�ʽ"NOR"����\n");

        if( (int)me->query_skill("sword",1) < 150 )
                return notify_fail("��Ļ��������ȼ�����������ʹ�á�"HIM"�̼�ʽ"NOR"����\n");

        if( (int)me->query_skill("force", 1) < 150 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á�"HIM"�̼�ʽ"NOR"����\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("�������̫��������ʹ�á�"HIM"�̼�ʽ"NOR"����\n");

        if( query("neili", me)<700 )
                return notify_fail("�������̫���ˣ��޷�ʹ�ó���\n");

        msg = WHT "\n$N����һ�Σ�����"+weapon->name()+WHT"�����缲�������һ���͹���$n���ü��У������ع���\n"
              "$NͻȻ��"+weapon->name()+WHT"������߲��һ�����죬�Ӳ���˼��ĽǶȴ�����$n�ļ�ͷ\n"NOR;

        msg = replace_string( msg, "song", songs[random(sizeof(songs))] );

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                addn("neili", -140, me);

                damage = damage_power(me, "sword");

                // if (target->is_busy()) damage = damage * 2;

                if( query("shen", target)<0)damage=damage*3/2;

                if( query("neili", me)>query("neili", target)*2 )
                        damage += random(damage);

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                p=query("qi", target)*100/query("max_qi", target);
                msg += COMBAT_D->damage_msg(damage, "����");
                msg += "( $n"+eff_status_msg(p)+" )\n";
                msg=replace_string(msg,"$w",query("name", weapon));
                msg = replace_string( msg, "$l", limbs[random(sizeof(limbs))] );
        }

        message_combatd(msg, me, target);

        msg = HIB "\n$n�ὣ��·����$N"+weapon->name()+HIB"ͣ�Ͳ�ǰ�������񽣷��̡���֪$n����ֻһ���䣬"
              "$N��"+weapon->name()+HIB"�綾�߱�����ǰһ̽���ѵ�����$n��ͷ����\n"NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp
                || target->is_busy())
        {
                me->start_busy(1);
                addn("neili", -150, me);
                damage = damage_power(me, "sword");
                // if(target->is_busy())damage=damage*2;
                if( query("shen", target)<0)damage=damage*3/2;

                if( query("neili", me)>query("neili", target)*2 )
                        damage += random(damage);

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                p=query("qi", target)*100/query("max_qi", target);
                msg += COMBAT_D->damage_msg(damage, "����");
                msg += "( $n"+eff_status_msg(p)+" )\n";
                msg=replace_string(msg,"$w",query("name", weapon));
                msg = replace_string( msg, "$l", limbs[random(sizeof(limbs))] );
        }
        message_combatd(msg, me, target);

        msg = YEL "\n$N"+weapon->name()+YEL"��һ�̣���һ����ÿһ�������ޱȹ���ķ�λ�̳���"
              "����$n�ļ粿��$nֻҪһ�����๥����ʱ��ɺ�����������$n�ļ�ͷ��\n"NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp
                ||target->is_busy())
        {
                addn("neili", -160, me);

                damage = damage_power(me, "sword");

                // if(target->is_busy())damage=damage*2;
                if( query("shen", target)<0)damage=damage*3/2;

                if( query("neili", me)>query("neili", target)*2 )
                        damage += random(damage);

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                p=query("qi", target)*100/query("max_qi", target);
                msg += COMBAT_D->damage_msg(damage, "����");
                msg += "( $n"+eff_status_msg(p)+" )\n";
                msg=replace_string(msg,"$w",query("name", weapon));
                msg = replace_string( msg, "$l", limbs[random(sizeof(limbs))] );
        }
        message_combatd(msg, me, target);

        return 1;
}