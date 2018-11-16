#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { HIW "�Ʊ�ժ��" NOR; }

int perform(object me, object target)
{
        object weapon;
        int level, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((level = me->query_skill("miaojia-jian", 1)) < 100)
                return notify_fail("����ҽ���������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<800 )
                return notify_fail("���������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "miaojia-jian")
                return notify_fail("��û�м�����ҽ���������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "һ���������������ţ����²�����˲����$n" HIW "����"
              "��������ͼ����$n" HIW "�Ĺ��ơ�\n" NOR;

        addn("neili", -30, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "���$p" HIR "ֻ��$P" HIR "���о��ȫȻ"
                       "�治��������ʵ�����Ƶ�ʱһ����\n" NOR;
                target->start_busy(level / 80 + 2);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "���Ƶ���·��"
                       "���Գ��У�˿����Ϊ������\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}