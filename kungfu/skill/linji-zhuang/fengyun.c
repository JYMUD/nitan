
// fengyun.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);

        if (level < 120) return notify_fail("����ټ�ʮ��ׯ��Ϊ��������\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("�������������ǿ��\n");

        if( query("neili", me)<4*level )
                return notify_fail("�������������\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("���Ѿ����˹��أ�ֻ��һ��������������Σ�գ�\n");

        if( query_temp("linji/fengyun", me) )
                return notify_fail("���ʱ��֫�ٺ������ĵ��������ٴ��˹���\n");

        set_temp("linji/fengyun", 1, me);
        write( HIY "�㰵�˷�����ׯ����˼����Ʈ��֮���л�����Ĭ���絴��֮Ѹ�ٽ�����\nһ�ɵ���������ע��֫�ٺ�������������������ࡣ\n" NOR);
        message("vision",
                HIY + "ֻ��" + me->name() + "΢��˫�ۣ���������һȦ����˲Ϣ��һ����������"+me->name()+"�����ָ�������\n" NOR,
                environment(me), me);

        addn("neili", -level, me);
        level /= 10;
        addn_temp("apply/dex", level, me);
        addn_temp("apply/attack", -level/2, me);
        addn_temp("apply/armor", level*15, me);
        addn_temp("apply/defense", level*5, me);

        me->start_call_out( (: call_other, __FILE__, "recover", me, level :), level * 10);

        return 1;
}

void recover(object me, int level)
{
        addn_temp("apply/dex", -level, me);
        addn_temp("apply/attack", level/2, me);
        addn_temp("apply/armor", -level*15, me);
        addn_temp("apply/defense", -level*5, me);
        delete_temp("linji/fengyun", me);

        tell_object(me, HIG"������й��Ѿã��Ծ����ĳ�����һЩ��\n"NOR);
}