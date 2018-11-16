// tiandi.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);

        if (level < 30) return notify_fail("����ټ�ʮ��ׯ��Ϊ��������\n");

        if (me->is_fighting())
                return notify_fail("ս���в���������ض�ׯ��\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("�������������ǿ��\n");

        if( query("neili", me)<4*level )
                return notify_fail("�������������\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("���Ѿ����˹��أ�ֻ��һ��������������Σ�գ�\n");

        if( query_temp("linji/tiandi", me) )
                return notify_fail("���Ѿ�������ض�ׯ�۾��������ˡ�\n");

        set_temp("linji/tiandi", 1, me);
        write( HIY "��ϯ�ض������������죬������ض�ׯ����������������Ǳ����������������ض�����̩�����پ��Լ��������������ˡ�\n" NOR);
        message_combatd(
                HIY + "ֻ��" + me->name() + "ϯ�ض������������죬���Ϻ��ʱ��ʱ�֣���һ�����������ĵ�վ��������\n" NOR,
                me);

        addn("max_qi", level*10, me);
        addn("max_jing", level*10, me);
        me->receive_curing("qi", level*10);
        me->receive_curing("jing", level*10);
        addn("jingli", level, me);
        addn("neili", -4*level, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, level :), 1800);

        return 1;
}

void remove_effect(object me, int level)
{
        addn("max_qi", -level*10, me);
        addn("max_jing", -level*10, me);
        if( query("eff_qi", me)>query("max_qi", me) )
                set("eff_qi",query("max_qi",  me), me);
        if( query("eff_jing", me)>query("max_jing", me) )
                set("eff_jing",query("max_jing",  me), me);
        delete_temp("linji/tiandi", me);

        tell_object(me, HIG"���������֮������ɢ�����֮�䣬���ָֻ���ԭ�о�����\n"NOR);
}