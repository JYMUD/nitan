// This program is a part of NT MudLIB
// jiuyang.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if( !query("can_exert/yijinjing/jiuyang", me) )
                return notify_fail("你还没有领悟过少林九阳真气呢！\n");

        if ((int)me->query_skill("yijinjing", 1) < 140)
                return notify_fail("你的易筋经修为如此之浅还想运用九阳真气？\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力修为太差，多多打坐吧。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够。\n");

        if( query_temp("sl/jiuyang", me) )
                return notify_fail("你已经在运真气增加攻击力。\n");

        skill = me->query_skill("yijinjing",1);
        message_combatd(HIR"\n$N潜运少林九阳神功，体内真气澎湃不息，全身佛光流动，宝相庄严！\n" NOR, me);

        addn_temp("apply/attack", skill, me);
        set_temp("sl/jiuyang", 1, me);
        addn("neili", -300, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill*2);
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}
void remove_effect(object me, int amount)
{
        if( query_temp("sl/jiuyang", me)){
                addn_temp("apply/attack", -amount, me);
                delete_temp("sl/jiuyang", me);
                message_vision(HIY"$N将九阳真气收回丹田，面露慈祥笑容。\n" NOR, me);
        }
}