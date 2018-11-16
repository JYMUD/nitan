#include <ansi.h>
#include <combat.h>

string name() { return HIR "�񵹹��������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;
        object weapon;
        string wname;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("ֻ�п��ֲ���ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 250)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("lingxiao-quan", 1) < 180)
                return notify_fail("�������ȭ��������죬����ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("cuff") != "lingxiao-quan")
                return notify_fail("��û�м�������ȭ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("cuff") != "lingxiao-quan")
                return notify_fail("������û��׼��ʹ������ȭ��������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        damage = damage_power(me, "cuff");
        ap = attack_power(me, "cuff");
        dp = defense_power(target, "parry");
        msg = HIR "$N" HIR "΢΢һЦ��ʩ�����񵹹����������������̽����ֱ��$n"
              HIR "�󾱡�\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "$P" HIR "���ּȿ죬��λ���棬$p"
                                           HIR "��αܵã�������$N" HIR "��ס��"
                                           "���ص�ˤ�ڵ��ϣ�\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "���Ʋ����æ������ס���ұۻӳ�����$P"
                       CYN "�ֱۡ�\n" NOR;
        }

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");
        msg += "\n" HIR "������$N" HIR "���桱��һ����������Ȼ̽�����������ץ��$n"
               HIR "��ǰ�ء�\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "$p" HIR "ֻ���ؿ�һ�飬�ѱ�$P"
                                           HIR "ץס�ؿڣ�����˳��һ˦����ʱƽ"
                                           "ƽ���˳�ȥ��\n" NOR);
        } else
        {
                msg += CYN "����$p" CYN "˿����Ϊ$P"
                       CYN "�����������񵲣����Ƚ���һ�мܿ���\n" NOR;
        }

        attack_power(me, "cuff");
        dp = defense_power(target, "force");
        msg += "\n" HIR "�ּ�$N" HIR "����һ���������������Ȳ����ҽ���ɨ$n"
               HIR "���̣�������Ű�ȥ��\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "���$p" HIR "�Բ����񣬶�ʱ��$P"
                                           HIR "���ڵأ�Ż��һ�����Ѫ��\n" NOR);
        } else
        {
                msg += CYN "Ȼ��$p" CYN "�����������ס���̣�����һ�ϣ�û��$P"
                       CYN "����\n" NOR;
        }
        me->start_busy(2 + random(3));
        addn("neili", -200, me);
        message_combatd(msg, me, target);
        return 1;
}
