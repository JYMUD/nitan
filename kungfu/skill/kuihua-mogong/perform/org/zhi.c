// zhi.c ��ڤ��ָ

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
 
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ڤ��ָֻ����ս���жԶ���ʹ�á�\n");

        if (me->query_skill("kuihua-mogong", 1) < 150)
                return notify_fail("��Ŀ���ħ����������죬����ʹ����ڤ��ָ��\n");

        if( query("neili", me)<300 )
                return notify_fail("�������������\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "������ǰ���漴һָ������Ϣ����$n" HIR "��Ҫ���̳���\n";

        me->want_kill(target);
        ap = me->query_skill("kuihua-mogong", 1);
        dp=query("combat_exp", target)/10000;
        addn("neili", -60, me);
        me->start_busy(1 + random(2));

        if (dp >= 100)
        {
                msg += HIC "$n" HIC "֪�����в��ƣ���æ���ܣ�û��һ������\n" NOR;
        } else
        if (random(ap) > dp)
        {
                msg += HIR "��һ���ٶ�֮����ȫ������$n" HIR "�����󣬱�$N"
                       HIR "��һָ���ô����˵���Ҫ��������������ʱ��ɢ��\n" NOR;
                message_combatd(msg, me, target);
                target->die(me);
                return 1;
        } else
        {
                msg += HIM "$n" HIM "���һ������æ�˺󣬾�Ȼ"
                      "���Ҷ㿪����һ�У�\n" NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}