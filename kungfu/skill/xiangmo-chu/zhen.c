// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "鎮魂舞" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "hammer" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("hammer") != "xiangmo-chu")
                return notify_fail("你沒有激發金剛降魔杵，難以施展" + name() + "。\n");

        if ((int)me->query_skill("xiangmo-chu", 1) < 100)
                return notify_fail("你金剛降魔杵火候不足，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "一聲斷喝，施出「" HIR "鎮魂舞" HIY "」絕技，寶相"
              "莊嚴，氣度萬千。手中" + weapon->name() + HIY "朝$n" HIY "連續"
              "砸下。\n" NOR;
        message_combatd(msg, me, target);

        addn("neili", -150, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(3));
        return 1;
}

