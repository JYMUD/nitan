#include <ansi.h>
#include <combat.h>

string name() { return HIY "���Ž���" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int level;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���в���ʹ�á�\n");

        if ((level = me->query_skill("jinguan-yusuo", 1)) < 150)
                return notify_fail("��Ľ��������������������ʩչ" + name() + "��\n" NOR);

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ�����㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n" NOR);

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "ͻȻ��$N" HIY "˫����Ļ�Ȧ��ʹ����" HIR "���Ž���"
              HIY "����������ͼ����$n" HIY "��������\n" NOR;

        ap = attack_power(me, "parry");
        dp = defense_power(target, "parry");

        if ( ap / 2 + random(ap) > dp )
        {
                msg += HIR "��ʱ$n" HIR "ֻ������һ����˫��̱��ȫ��"
                       "�������Ʊ�$N" HIR "������ס��\n" NOR;
                target->start_busy(ap / 80 + 2);
                addn("neili", -100, me);
                me->start_busy(1);
        } else
        {
                msg += HIC "����$n" HIC "�������ܣ�˿����Ϊ$N"
                       HIC "���������ҡ�\n" NOR;
                addn("neili", -50, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}