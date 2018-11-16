#include <ansi.h>

inherit F_SSERVER;

string name() { return HIG "������Ϊ" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ����"
                                   "�������ɡ�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("����������ԣ��޷�ʩչ" + name() + "\n");

        if (me->query_skill("sanwu-shou", 1) < 70)
                return notify_fail("������������ּ��𲻹����޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("whip") != "sanwu-shou")
                return notify_fail("��û�м������������֣��޷�ʩչ " + name() + "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "\n$N����һ����Ǳ������������ʩ�����С�" HIG "������Ϊ" HIY
              "����" + weapon->name() + HIY "����ú���ֱ�죬\n������ң���$n"
              HIY "������" + weapon->name() + "�Ĺ���֮�¡�" NOR;
        me->start_busy(2);

        message_combatd(msg, me, target);

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        if( ap / 2 + random(ap) > dp )
        {
                msg = HIR "$n" HIR "ֻ��������������ǰ��ǧ��Ӱ���ٸ�"
                      "�ֽ��޴룬���Ų��ѡ�\n" NOR;
                target->start_busy((int)me->query_skill("sanwu-shou") / 80 + 2);
        } else
        {
                msg = CYN "����$p" CYN "������$P"
                      CYN "����ͼ��б������������\n" NOR;
        }
        addn("neili", -80, me);
        message_combatd(msg, me, target);

        return 1;
}