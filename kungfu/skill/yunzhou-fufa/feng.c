#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "��ħ��" NOR; }

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

        if (me->query_skill("yunzhou-fufa", 1) < 60)
                return notify_fail("�������������𲻹����޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("whip") != "yunzhou-fufa")
                return notify_fail("��û�м�������������޷�ʩչ" + name() + "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "\n$N����һ����Ǳ��������������" + weapon->name() + HIY
              "����ú���ֱ�죬ֱ�Ƴ��գ����������ɳ�����$n��\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        if( ap / 2 + random(ap) > dp )
        {
                msg += HIR "$n" HIR "ֻ��������������ǰ��ǧ��Ӱ���ٸ�"
                      "�ֽ��޴룬���Ų��ѡ�\n" NOR;

                target->start_busy((int)me->query_skill("yunzhou-fufa") / 25 + 2);
        } else
        {
                msg += CYN "����$p" CYN "������$P"
                      CYN "����ͼ��б������������\n" NOR;
        }
        me->start_busy(1);

        addn("neili", -80, me);
        message_combatd(msg, me, target);

        return 1;
}