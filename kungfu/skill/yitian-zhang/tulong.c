// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "��������"; }

int perform(object me, object target)
{
        string msg, pmsg;
        int damage, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target
        ||      ! target->is_character()
        ||      ! me->is_fighting(target))
                return notify_fail("ǣ�ƹ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_str() < 30)
                return notify_fail("���������,����ʹ����һ����!\n");

        if ((int)me->query_skill("yinyun-ziqi", 1) < 100)
                return notify_fail("���������Ĺ�����������ʹ��������������!\n");

        if( query("neili", me)<800 )
                return notify_fail("���������ڲ���, ����ʹ����������! \n");

        msg = HIY "$N��Хһ����" + YEL "�������𡢱����������������£�Ī�Ҳ��ӡ����첻����˭�����棿\n" +
              HIY "������������������������������������ڣ����������������������ʮ����һ��д�ϡ�\n"NOR;

        ap=attack_power(me, "strike");

        dp=defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                addn("neili", -500, me);

                if (damage < 20)
                        pmsg = HIY"���$n�ܵ�$N�����������ƺ�һ����\n"NOR;
                else if (damage < 40)
                        pmsg = HIY"���$n��$N���������𣬡��١���һ������������\n"NOR;
                else if (damage < 80)
                        pmsg = RED"���$n��$N������һ���ؿ������ܵ�һ���ش�����������������\n"NOR;
                else
                        pmsg = HIR"���$n��$N������һ����ǰһ�ڣ���һ������һ���ɳ�ȥ�ü���Զ��\n"NOR;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 35, pmsg);

                me->start_busy(2);
                target->start_busy(random(3));

        }
        else
        {
                me->start_busy(2);
                addn("neili", -200, me);
                msg += CYN"����$p������$P����ͼ����û���ϵ�������һ����㿪�ˡ�\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}