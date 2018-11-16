
// daxiao.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);
        int amount;

        if (level < 150) return notify_fail("����ټ�ʮ��ׯ��Ϊ��������\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("�������������ǿ��\n");

        if( query("neili", me)<4*level )
                return notify_fail("�������������\n");

        if( query("eff_qi", me)<query("max_qi", me) )
                return notify_fail("��������Ѫ���ˣ�ֻ���޷����ھ���ƽ�⣡\n");

        if( query("eff_jing", me)<query("max_jing", me) )
                return notify_fail("�����ھ������ˣ�ֻ���޷����ھ���ƽ�⣡\n");

        if( query_temp("linji/daxiao", me) )
                return notify_fail("���Ѿ��˹����ھ�����С�ˡ�\n");

        set_temp("linji/daxiao", 1, me);
        write( HIY "����Ϣ�������������д�С��ׯ��ֻ��һ��ů�������ţ����ػ�������ȫ��������һ�ܣ����뵤��������\n" NOR);
        message_combatd(
                HIY + "ֻ��" + me->name() + "��Ϣ������ͷ��Ʈ��һ���ư�������̬����ƣ����\n" NOR,
                me);

        amount=query("max_jing", me)-query("max_qi", me);
        amount /= 2;

        addn("max_qi", amount, me);
        addn("max_jing", -amount, me);
        set("eff_qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        if( query("qi", me)>query("max_qi", me) )
                set("qi",query("max_qi",  me), me);
        if( query("jing", me)>query("max_jing", me) )
                set("jing",query("max_jing",  me), me);

        addn("neili", -4*level, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, amount :), 1800);

        return 1;
}

void remove_effect(object me, int level)
{
        addn("max_qi", -level, me);
        addn("max_jing", level, me);
        set("eff_qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        if( query("qi", me)>query("max_qi", me) )
                set("qi",query("max_qi",  me), me);
        if( query("jing", me)>query("max_jing", me) )
                set("jing",query("max_jing",  me), me);
        delete_temp("linji/daxiao", me);

        tell_object(me, HIG"���д�С��ׯ�Ѿã��ָֻ���ԭ�о�����\n"NOR);
}