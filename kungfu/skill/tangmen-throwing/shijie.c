#include <ansi.h>
#include <combat.h>

string name() { return HIM "一花一世界" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int ap, dp, damage;
        string msg;
        object weapon;

        if( !query("reborn/times", me) ) 
                return notify_fail("你尚未转世重生，无法使用" + name() + "。\n"); 
                
        if( !target) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail(name() + "只能在战斗中对对手使用。\n");
        
        if( me->is_busy() )
                return notify_fail("你正在忙着呢。\n"); 

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你现在手中没有拿着暗器，难以施展" + name() + "。\n");

        if( (skill = me->query_skill("tangmen-throwing", 1)) < 800 )
                return notify_fail("你的唐门暗器不够娴熟，难以施展" + name() + "。\n");

        if( (int)me->query_skill("boyun-suowu", 1) < 800 )
                return notify_fail("你的拨云锁雾不够娴熟，无法施展" + name() + "。\n");

        if( (int)me->query_skill("force") < 800 )
                return notify_fail("你的内功修为不足，难以施展" + name() + "。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me) < 1500 )
                return notify_fail("你现在真气不足，难以施展" + name() + "。\n");

        if( !living(target) )
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        addn("neili", -1000, me);

        msg = HIM "\n$N" HIM "手中突然多了一支花，美得妖艳，$n" HIM "觉得有点痴了，\n"
              HIM "$n" HIM "不知不觉中进入了一花一世界中。\n" NOR;

        ap = attack_power(me, "throwing") * 2;
        dp = defense_power(target, "parry") + defense_power(target, "dodge") +
             target->query_skill("dugu-jiujian", 1) * 10;

        message_combatd(msg, me, target);

        if (ap * 2 / 3 + random(ap * 3 / 2) > dp)
        {
                msg = HIR"那花越开越艳，一花一世界，一木一浮生，$n"HIR"微笑着倒下了，那花也谢了。\n" NOR;
                weapon->hit_ob(me,target,query("jiali", me)+200);
                //weapon->move(target);
                weapon->add_amount(-1);

                message_combatd(msg, me, target);
                target->receive_damage("qi", query("max_qi", target), me);
                target->receive_wound("qi", query("max_qi", target), me);
                COMBAT_D->report_status(target);
/*
                COMBAT_D->clear_ahinfo();
                target->unconcious(me);
*/
                me->start_busy(2);
        } else
        {
                msg = HIR "危急时刻，$n " HIR "顿悟一方一净土，从花的世界中遁出，那花划空而过。只听当的一声轻响，那花谢了，轻轻地砸在地面上。\n" NOR;
                message_combatd(msg, me, target);
                if( query("neili", target)<1000 )
                        set("neili", 0, target);
                else
                        addn("neili", -1000, target);
                //weapon->move(environment(me));
                weapon->add_amount(-1);
                
                me->start_busy(3);
                target->set_weak(10);
                target->affect_by("poison", 
                        ([ "level" : 8000, 
                           "id":query("id", me), 
                           "name" : "唐门花毒", 
                           "duration" : 200 ])); 
                tell_object(target, HIG "你中了唐门一花一世界的花毒。\n"); 
        }
        return 1;
}


