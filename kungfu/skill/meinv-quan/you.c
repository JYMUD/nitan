// This program is a part of NITAN MudLIB
// you.c ��Ĺ�ľ�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "��Ĺ�ľ�" NOR; }

int perform(object me, object target)
{
        int damage, ap, dp;
        string msg;
        string pmsg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon"))
                return notify_fail("�������ֲ���ʩչ" + name() + "��\n");

        if ((int)me->query_skill("meinv-quan", 1) < 80)
                return notify_fail("�����Ůȭ���𲻹�������ʹ��" + name() + "��\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���δ��죬����ʹ��" + name() + "��\n");

        if ((int)me->query("neili") < 180)
                return notify_fail("��������������������ʹ��" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "meinv-quan")
                return notify_fail("��û�м�����Ůȭ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "meinv-quan")
                return notify_fail("��û��׼����Ůȭ��������ʩչ" + name() + "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "\n$N" HIW "����֧�ã���������ӳ�����̾һ����ʹ"
              "����Ĺ�ɾ�ѧ����Ĺ�ľӡ���һ�����ּ���֮�⡣\n" NOR;

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1+random(2));

                damage = damage_power(me, "unarmed");

                addn("neili", -100, me);

                if (damage < 30)
                        pmsg = HIY "���$n" HIY "��$N��"
                               HIY "��һ�����ƺ�һ����\n" NOR;
                else if(damage < 55)
                        pmsg = HIY "���$n" HIY "��$N"
                               HIY "������һ���������ڡ����˳�������\n" NOR;
                else if (damage < 80)
                        pmsg = HIR "���$n" HIR "��$N"
                               HIR "������һ�����ؿ������ܵ�һ����"
                               "������ѪΪ֮һ�ϣ�\n" NOR;
                else if (damage < 100)
                        pmsg = RED "���$n" RED "��$N" RED
                               "������һ������ǰһ�ڣ�������Ѫ���ڣ�"
                               "���������¯һ�㣡\n" NOR;
                else
                        pmsg = HIR "����$N" HIR "˫ȭϮ�������д��գ�Ѹ"
                               "���ޱȣ����·��̲��������������$n" HIR
                               "�����ɼ䣬ȴ����ȭ���ƺ�һ������"
                               "�˼�����һ����Ѫ�����\n" NOR;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50, pmsg);
        } else
        {
                me->start_busy(3);
                msg += CYN "����$p" CYN "������$P" CYN
                       "����ͼ������̩ɽ��̧��һ�ܸ���$P"
                       CYN "��һȭ��\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}