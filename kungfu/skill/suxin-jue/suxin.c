
// suxin.c


#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("suxin-jue", 1);

        if (level < 120) return notify_fail("你的内功修为还不够。\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("你的内力还不够强。\n");

        if( query("neili", me)<4*level )
                return notify_fail("你的真气不够。\n");

        if( query_temp("ngsuxin", me) )
                return notify_fail("你此时正在按素心诀的心法行功。\n");

        set_temp("ngsuxin", 1, me);
        write( HIW "你暗运玉女素心心法，把多年修炼的“十二少、十二多”的正反要诀发挥到极致。\n" NOR);
        message("vision",
                HIW + "只见" + me->name() + "微闭双眼，无喜无乐，无思无虑,把多年修炼的“十二少、十二多”的正反要诀发挥到极致。\n" NOR,
                environment(me), me);

        addn("neili", -level, me);
        addn_temp("apply/armor", level, me);
        addn_temp("apply/defense", level, me);

        me->start_call_out( (: call_other, __FILE__, "recover", me, level :), 500);

        return 1;
}

void recover(object me, int level)
{
        delete_temp("ngsuxin", me);
        addn_temp("apply/armor", -level, me);
        addn_temp("apply/defense", -level, me);

        tell_object(me, HIG"你行功已久，慢慢收回玉女素心的心法。\n"NOR);
}