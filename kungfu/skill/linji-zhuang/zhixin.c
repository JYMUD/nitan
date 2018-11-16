// zhixin.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);

        if (level < 60) return notify_fail("����ټ�ʮ��ׯ��Ϊ��������\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("�������������ǿ��\n");

        if( query("neili", me)<4*level )
                return notify_fail("�������������\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("���Ѿ����˹��أ�ֻ��һ��������������Σ�գ�\n");

        if( query_temp("linji/zhixin", me) )
                return notify_fail("���Ѿ�����֮�Ķ�ׯ���������ˡ�\n");

        set_temp("linji/zhixin", 1, me);
        write( HIY "��΢һ�����˶�֮����ׯ��ȥ���������⣬�����������У�ֻ����̨�������������ƺ��������ӡ�\n" NOR);
        message("vision",
                HIY + "ֻ��" + me->name() + "΢һ�������¼��ڳ�����һ�������鶯������������ġ�\n" NOR,
                environment(me), me);

        addn("neili", -4*level, me);
        level += me->query_skill("literate", 1);
        level = 1+random(level)/16;
        addn_temp("apply/int", level, me);
        set("jiali", 0, me);

        me->start_call_out( (: call_other, __FILE__, "recover", me, level :), 1800);

        return 1;
}

void recover(object me, int level)
{
        addn_temp("apply/int", -level, me);
        delete_temp("linji/zhixin", me);

        tell_object(me, HIG"�������ѻ������������ƺ��������ֹ���Ѱ����\n"NOR);
}