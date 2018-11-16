
// suxin.c


#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("suxin-jue", 1);

        if (level < 120) return notify_fail("����ڹ���Ϊ��������\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("�������������ǿ��\n");

        if( query("neili", me)<4*level )
                return notify_fail("�������������\n");

        if( query_temp("ngsuxin", me) )
                return notify_fail("���ʱ���ڰ����ľ����ķ��й���\n");

        set_temp("ngsuxin", 1, me);
        write( HIW "�㰵����Ů�����ķ����Ѷ��������ġ�ʮ���١�ʮ���ࡱ������Ҫ�����ӵ����¡�\n" NOR);
        message("vision",
                HIW + "ֻ��" + me->name() + "΢��˫�ۣ���ϲ���֣���˼����,�Ѷ��������ġ�ʮ���١�ʮ���ࡱ������Ҫ�����ӵ����¡�\n" NOR,
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

        tell_object(me, HIG"���й��Ѿã������ջ���Ů���ĵ��ķ���\n"NOR);
}