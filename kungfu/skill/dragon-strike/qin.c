#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "������" NOR; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", target)) )
                return notify_fail("�Է�û��ʹ�ñ���������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 260)
                return notify_fail("���ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("��������Ϊ����������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("dragon-strike", 1) < 180)
                return notify_fail("�㽵��ʮ���ƻ�򲻹�������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "dragon-strike")
                return notify_fail("��û�м�������ʮ���ƣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("��û��׼������ʮ���ƣ�����ʩչ" + name() + "��\n");

        if( query("neili", me)<400 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "����һ����ȫ���ھ��ŷ��������ұ۷����⳶����ͼ��$n"
              HIR "��" + weapon->name() + HIR "�������С�\n" NOR;

        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "parry") + target->query_int()*10;

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -300, me);
                msg += HIR "$n" HIR "ֻ����Χ����ӿ��������" + weapon->name()
                       + HIR "��Ȼ����ס����$N" HIR "�������ַ�ȥ��\n" NOR;
                me->start_busy(2);
                weapon->unequip();
                weapon->move(me, 1);
        } else
        {
                addn("neili", -200, me);
                msg += CYN "$n" CYN "ֻ����Χ����ӿ������æ����������"
                       + weapon->name() + CYN "������ܲ�͸�磬ʹ��$N"
                       CYN "�޴����֡�\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}
