// This program is a part of NITAN MudLIB
// hama.c ��󡹦

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "������"; }

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int damage, p, ap, dp;
        string msg, dodge_skill;

        if (! target) target = offensive_target(me);

        if (! target || !target->is_character() ||
            ! me->is_fighting(target) ||
            ! living(target))
                return notify_fail("���������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("hamagong", 1) < 100)
                return notify_fail("��ĸ�󡹦����������������ʹ��������ԵУ�\n");

        if( query_temp("weapon", me) )
                return notify_fail("�������ֲ���ʹ�á������졹��\n");

        if (me->query_skill_mapped("force") != "hamagong")
                return notify_fail("����ڹ����޴˹���\n");

        if (me->query_skill_prepared("strike") != "hamagong" ||
            me->query_skill_mapped("strike") != "hamagong")
                return notify_fail("������Ƚ���󡹦�������Ʒ�֮�в��С�\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("�������������㣬ʹ������󡹦�ľ��������죡\n");

        if( query("neili", me)<400 )
                return notify_fail("�������������㣬ʹ������󡹦�ľ��������죡\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("����Ʒ�������죬ʹ������󡹦�ľ��������죡\n");

        if (me->query_str() < 30 )
                return notify_fail("�������̫С��ʹ�����ø����������죡\n");

        msg = BLU "\n$N���Ӷ��£�����ƽ�ƶ�����ʹ������$N��ƽ�����ġ������졹���У��Ʒ�ֱ��$n��ȥ��\n"NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                if (! target->is_busy())
                        target->start_busy(1);

                addn("neili", -200, me);

                damage = damage_power(me, "force");
                if( query("neili", me)>random(query("neili", target)) )
                        damage += query("jiali", me);
                damage *= 2;

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);

                p=query("eff_qi", target)*100/query("max_qi", target);
                msg += COMBAT_D->damage_msg(damage, "����");
                msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                call_out("perform2", 1, me, target, p, damage);
        } else
        {
                me->start_busy(2);
                if (! target->is_busy())
                        target->start_busy(1);

                addn("neili", -100, me);
                tell_object(target, HIY"�㵫��һ��΢�����������������Ȼ������Ȼ�ѱƵ��Լ�����������֪�������æԾ�����ߡ�\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_combatd(msg, me, target);
        return 1;
}

int perform2(object me, object target, int p, int damage)
{
        int ap, dp;
        string msg, dodge_skill;

        if( !target || !me || !living(me)
           || !me->is_fighting(target)
           || environment(target)!=environment(me) || !living(target))
                return 0;

        if( query("neili", me)<500 )
                return notify_fail("���Ҫ�ٷ�һ�ƣ�ȴ�����Լ������������ˣ�\n");

        msg = BLU "\n$N���ƾ���δ��������Ҳ�����Ƴ�������������������졹�Ʒ���ɽ������ӿ��$n��\n"NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                if (! target->is_busy())
                        target->start_busy(1);

                addn("neili", -300, me);

                if( query("neili", me)>random(query("neili", target)) )
                        damage += query("jiali", me);
                damage *= 2;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                p=query("qi", target)*100/query("max_qi", target);
                msg += COMBAT_D->damage_msg(damage, "����");
                msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                call_out("perform3", 1, me, target, p, damage);
        }
        else
        {
                me->start_busy(2);
                if (! target->is_busy())
                        target->start_busy(1);
                addn("neili", -200, me);
                tell_object(target, HIY"�㴭Ϣδ�����־�һ�ɾ��������������æԾ�����ߣ��Ǳ��رܿ���\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target);
        return 1;
}

int perform3(object me, object target, int p, int damage)
{
        int ap, dp;
        string msg, dodge_skill;

        if(! target || ! me || environment(me) != environment(target)) return 1;
        if(!living(target))
              return notify_fail("�����Ѿ�������ս���ˡ�\n");

        if( query("neili", me)<700 )
                return notify_fail("���Ҫ�ٷ�һ�ƣ�ȴ�����Լ������������ˣ�\n");

        msg = BLU "\n$N˫��һ�ǣ�˫���ಢ��ǰ�����Ƴ���$n��ͬ��ǰ��Բ����ȫ�ڡ������졹��������֮�£�\n"NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                if (! target->is_busy())
                        target->start_busy(2);

                addn("neili", -400, me);

                if( query("neili", me)>random(query("neili", target)) )
                        damage += query("jiali", me);
                damage *= 2;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                p=query("eff_qi", target)*100/query("max_qi", target);
                msg += COMBAT_D->damage_msg(damage, "����");
                msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
        } else
        {
                me->start_busy(2);
                if (! target->is_busy())
                        target->start_busy(1);
                addn("neili", -300, me);
                addn("jingli", -100, target);
                tell_object(target, HIY"���þ�ȫ����������һ��һ����ҡҡ������վ��������������㿪����������һ����\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }

        message_combatd(msg, me, target);
        return 1;
}
