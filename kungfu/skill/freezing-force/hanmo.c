// This program is a part of NT MudLIB

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;

        if( !query("reborn/times", me) )
                return notify_fail("你尚未转世重生，无法使用寒魔玄力！\n");

        if( target != me )
                return notify_fail("你只能用冰蚕寒功来激发寒魔玄力。\n");

        if( (skill = me->query_skill("freezing-force", 1)) < 1500 )
                return notify_fail("你的冰蚕寒功修为不够，无法使用寒魔玄力！\n");

        if( me->query_skill("huagong-dafa", 1) < 1500 )
                return notify_fail("你的化功大法修为不够，无法使用寒魔玄力！\n");

        if( me->query_skill("poison", 1) < 1500 )
                return notify_fail("你对基本毒功的参悟还不够，无法使用寒魔玄力！\n");

        if( me->query_skill("force", 1) < 1500 )
                return notify_fail("你对基本内功的修为还不够，无法使用寒魔玄力！\n");

        if( query_temp("freezing", me) )
                return notify_fail("你已经在运起寒魔玄力了。\n");

        if( query("jingli", me)<2000 )
                return notify_fail("你的真气不够。\n");

        if( query("neili", me)<5000 )
                return notify_fail("你的内力不够。\n");

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);

        message_combatd(HIB "$N" HIB "神色凝重，深吸一口气，体表瞬间变为靛蓝色，$N" HIB "随之摆出各种奇特的造型舞动着。\n"
                       "随着那些诡异的舞姿，蓝色烟气四起，在空中竟似显现无数异样蚕虫，在$N身周绕行不止，\n"
                       "四周温度骤降，只刹那间功夫，空气似乎都凝结了。这瞬间，$N" HIB "如同毒神附体，使人周身颤栗。\n" NOR, me);

        addn_temp("apply/unarmed_damage", 9000, me);
        addn_temp("apply/avoid_freeze", 90, me);
        addn_temp("apply/add_freeze", 90, me);
        addn_temp("apply/add_poison", 90, me);
        set_temp("freezing", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill/10);

        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me)
{
        if( query_temp("freezing", me)){
                addn_temp("apply/add_freeze", -90, me);
                addn_temp("apply/add_poison", -90, me);
                addn_temp("apply/unarmed_damage", -9000, me);
                addn_temp("apply/avoid_freeze", -90, me);
                delete_temp("freezing", me);
                tell_object(me, HIB "$N" HIB "身形一滞，略显蹒跚，将冰蚕寒魔玄力收回丹田，"
                                "随着真气凝成的蚕虫纳入体内，\n$N" HIB"的体色恢复正常，周围的寒气也慢慢散开了。\n" NOR);
        }
}
