// This is player's own perform (Write by Lonely@nt2)
//Createby易水寒(Rain)atWed Aug 20 00:46:17 2014
// 狂风刀诀(kuang)
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "狂风刀诀" NOR; }

string *weapon_sk = ({
        "sword", "blade", "staff", "whip", "club", "hammer", "axe"
});

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (member_array("blade", weapon_sk) != -1)
        {
                if( !objectp(weapon=query_temp("weapon", me) )
                    || query("skill_type", weapon) != "blade" )
                        return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");
        } else
        {
                if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                        return notify_fail(name() + "只能空手使用。\n");
        }

        if ((int)me->query_skill("mad-blade", 1) < 400)
                return notify_fail("你" + to_chinese("mad-blade") + "不够娴熟，难以施展" + name() + "。\n");

        if (member_array("blade", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("blade") != "mad-blade")
                        return notify_fail("你没有准备" + to_chinese("mad-blade") + "，难以施展" + name() + "。\n");
        }

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N手中武器刀势连连，周身狂风突起，无数风刃徐徐而起，$n感觉要被风刃撕碎了！" + "\n" + NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");
        attack_time = 6;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += HIM "只见风刃连连击中$n，全身上下鲜血汹涌喷出！" + "\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
                addn_temp("apply/damage", count, me);
        } else
        {
                msg += NOR + CYN "$p见势不妙，抽身急退，险险避过$P的这记杀招。" + "\n" NOR;
                count = 0;
        }

        message_sort(msg, me, target);

        attack_time+=query("jieti/times", me)*2;
        if (attack_time > 13)
                attack_time = 13;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) && ! target->is_busy()) target->start_busy(1);

                COMBAT_D->do_attack(me, target, (member_array("blade", weapon_sk) == -1 ? 0 : weapon), 0);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(3 + random(attack_time/ 3));

        return 1;
}
