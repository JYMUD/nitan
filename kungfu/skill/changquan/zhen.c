// gladiator

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "�����־�" NOR; }

int perform(object me, object target)
{
        string msg;
        int i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name()+"ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("changquan", 1) < 80)
                return notify_fail("��̫�泤ȭ������죬����ʩչ"+name()+"��\n");

        if (me->query_skill_mapped("cuff") != "changquan")
                return notify_fail("��û�м���̫�泤ȭ������ʩչ"+name()+"��\n");

        if (me->query_skill_prepared("changquan") != "changquan")
                return notify_fail("��û��׼��̫�泤ȭ������ʩչ"+name()+"��\n");

        if( query("neili", me)<100 )
                return notify_fail("�������������㣬����ʩչ"+name()+"��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "��ʱ��ֻ��$N" HIY "���������ȶ����̣�˫ȭ�����з������λ���$n"
              HIY "ȫ�������\n" NOR;
        message_combatd(msg, me, target);
        addn("neili", -50, me);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(1 + random(3));
        return 1;
}