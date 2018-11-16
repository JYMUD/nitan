#include <ansi.h>
#include <combat.h>

string name() { return HIR "��Ӱ��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if ((level = (int)me->query_skill("tie-zhang", 1)) < 100)
                return notify_fail("�������Ʒ���򲻹�������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "tie-zhang")
                return notify_fail("��û�м��������Ʒ�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "tie-zhang")
                return notify_fail("��û��׼�������Ʒ�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("���������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "˫�ƽ���ʩ�����ƾ�����" HIR "��Ӱ��" NOR +
              WHT "�����������Ӱ������$n" WHT "�ķ���\n" NOR;

        ap=attack_power(me,"strike")+me->query_str()*15;
        dp=defense_power(target,"parry")+target->query_dex()*15;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "��Ӱ�ζ���$n" HIR "��ʽ��Ȼһ��������$N"
                       HIR "������ǣ������æ���ң�\n" NOR;
                target->start_busy(ap / 80 + 2);
                me->start_busy(1);
                addn("neili", -100, me);
        } else
        {
                msg += CYN "����$n" CYN "������$N"
                       CYN "����ͼ���򶨽��У�һ˿���ҡ�\n" NOR;
                me->start_busy(2);
                addn("neili", -80, me);
        }
        message_combatd(msg, me, target);

        return 1;
}