
#include <ansi.h>
#include <combat.h>

string name() { return HIG "����Ʈ��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if ((int)me->query_skill("huashan-zhang", 1) < 30)
                return notify_fail("��Ļ�ɽ�Ʒ�������죬����ʹ��" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "huashan-zhang")
                return notify_fail("��û��׼��ʹ�û�ɽ�Ʒ����޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<60 )
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIM "\n��Ȼ��$N" HIM "˫�Ʋ�������$n" HIM "������������������;�к�����\n"
              "�����������������������ʵʵ��Ʈ�첻�������ǻ�ɽ���С�" HIG  "����Ʈ��" HIM
              "���� \n��̽�$n" HIM "�ѱ�$N" HIM "�Ʒ����֡�\n" NOR;

        addn("neili", -30, me);
        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "���$p" HIR "һʱ�޷����������ʵ�����޷�ʩ�С�\n" NOR;
                target->start_busy(ap / 100 + 2);
        } else
        {
                msg += CYN "����$n" CYN "����������ʵ��������ᡣ\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}