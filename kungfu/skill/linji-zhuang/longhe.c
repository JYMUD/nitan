// longhe.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);
        int jingli, jing, extrajing;

        if (level < 90) return notify_fail("����ټ�ʮ��ׯ��Ϊ��������\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("�������������ǿ��\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("���Ѿ����˹��أ�ֻ��һ��������������Σ�գ�\n");

        if( query("eff_jing", me)<query("max_jing", me)/2 )
                return notify_fail("���Ѿ����˹��أ�ֻ��һ��������������Σ�գ�\n");

        extrajing=query("jing", me)-query("max_jing", me)/2;
        if (extrajing < 1)
                return notify_fail("��ľ���̫�");

        if( query("neili", me)<1 )
                return notify_fail("�������������\n");

        jingli=query("max_jingli", me)-query("jingli", me);
        if ( jingli < 10 )
                return notify_fail("�����ھ������档\n");
        jing = 90*jingli/level;
        if (jing < 5) jing = 5;
        if (extrajing < jing) {
                jingli = jingli * extrajing / jing;
                jing = extrajing ;
        }
        addn("jing", -jing, me);
        addn("jingli", jingli, me);

        write( HIY "�㰵��������ׯ�������ţ��յػ����۾��������پ�����������\n" NOR);
        message("vision",
                HIY + "ֻ��" + me->name() + "����ƣ������ת˲��㾫���ӡ�\n" NOR,
                environment(me), me);

        return 1;
}