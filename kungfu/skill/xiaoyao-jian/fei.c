// This program is a part of NT MudLIB
#include <ansi.h>
#include <combat.h>

string name() { return HIW "�ɽ���" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg, wn;
        object weapon;
        int level;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((int)me->query_skill("xiaoyao-jian", 1) < 60)
                return notify_fail("����ң����������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "xiaoyao-jian")
                return notify_fail("��û�м�����ң����������ʩչ" + name() + "��\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("����Ṧ��Ϊ����������ʩչ" + name() + "��\n");

        if ((int)query("neili", me) < 200)
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();

        msg = HIC "\n$N" HIC "��Ȼ����죬�����鶯�ޱȣ�����" + wn + HIC "��"
              "�����ַ���һ�㣬��$n" HIC "�������֡�\n" NOR;

        message_combatd(msg, me, target);

        level = me->query_skill("sword");

        addn("neili", -120, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIY "$N" HIY "������$n" HIY "��ʽ�е���ʵ����æ"
                      "��ס�Լ�ȫ��һʱ������Ӧ�ԣ�\n" NOR;
                target->start_busy(4 + random(level / 25));
                me->start_busy(random(2));
        } else
        {
                msg = CYN "����$N" CYN "��������С�Ĳ��У�û�б�"
                      "$n" NOR + CYN "��ʽ������\n" NOR;

                me->start_busy(2);
        }
        message_combatd(msg, target, me);

        return 1;
}