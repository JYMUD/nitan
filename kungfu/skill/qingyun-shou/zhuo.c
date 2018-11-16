// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return WHT "����׽Ӱ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("qingyun-shou", 1) < 50)
                return notify_fail("��������ֲ�����죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("hand") != "qingyun-shou")
                return notify_fail("��û�м��������֣�����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("hand") != "qingyun-shou")
                return notify_fail("������û��׼��ʹ�������֣�����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "����������ַ�������Ӱ����ʵʵ���ѱ���α����"
              "ȫ����$n" WHT "��\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "hand");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "$p" HIR "һʱ�������ʵ����$P"
                                           HIR "��Ӱ�������ţ���Ѫ������������Ϣ��\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -100, me);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
