#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "佛光普照" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必须空手才能施展" + name() + "。\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的内功的修为不够，无法施展" + name() + "。\n");

        if (me->query_skill("piaoxue-zhang", 1) < 180)
                return notify_fail("你的飘雪穿云掌修为不够，无法施展" + name() + "。\n");

        if( query("neili", me)<1000 || query("max_neili", me)<3500 )
                return notify_fail("你的真气不够，无法施展" + name() + "。\n");

        /*
        if (me->query_skill_mapped("force") != "emei-jiuyang" &&
            me->query_skill_mapped("force") != "wudang-jiuyang" &&
            me->query_skill_mapped("force") != "shaolin-jiuyang" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("你没有激发内功为九阳神功，无法施展" + name() + "。\n");
        */

        if (me->query_skill_mapped("strike") != "piaoxue-zhang")
                return notify_fail("你没有激发飘雪穿云掌，无法施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "piaoxue-zhang")
                return notify_fail("你没有准备飘雪穿云掌，无法施展" + name() + "。\n");

        if( !query_temp("powerup", me) )
                return notify_fail("你必须将全身功力尽数提起才能施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "运起全身功力，顿时真气迸发，全身骨骼噼啪作"
              "响，猛然一掌向$n" HIY "\n全力拍出，力求一击毙敌，正是一"
              "招「佛光普照」。\n" NOR;

        ap = attack_power(me, "strike") +
             me->query_skill("force") +
             query("str", me)*10;

        dp = defense_power(target, "dodge") +
             target->query_skill("force") +
             query("con", me)*10;

        if (target->query_skill_mapped("force") == "jiuyang-shengong")
        {
                addn("neili", -800, me);
                me->start_busy(5);
                msg += HIW "只听轰然一声巨响，$n" HIW "已被一招正中，可$N"
                       HIW "只觉全身内力犹如江河入\n海，又如水乳交融，登"
                       "时消失得无影无踪。\n" NOR;
        } else
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike") + me->query_skill("mahayana", 1);
                addn("neili", -800, me);
                me->start_busy(3);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                           HIR "只听轰然一声巨响，$n" HIR "被$N"
                                           HIR "一招正中，身子便如稻草般平平飞出"
                                           "，重\n重摔在地下，呕出一大口鲜血，动"
                                           "也不动。\n" NOR);
        } else
        {
                addn("neili", -500, me);
                me->start_busy(4);
                msg += CYN "可是$p" CYN "内力深厚，及时摆脱了"
                       CYN "$P" CYN "内力的牵扯，躲开了这一击！\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
