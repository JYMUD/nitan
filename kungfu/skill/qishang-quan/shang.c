// This program is a part of NITAN MudLIB
// shang.c ���־�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "���־�" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("qishang-quan", 1) < 120)
                return notify_fail("�������ȭ������죬�޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force", 1) < 120)
                return notify_fail("����ڹ���Ϊ���������޷�ʩչ" + name() + "\n");

        if ((int)query("neili", me) < 300)
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("��û��׼��ʹ������ȭ���޷�ʩչ" + name() + "��\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "ŭ��һ����ʩ�����С�" HIW "���־�" HIY "����˫ȭѸ���ޱ�"
              "��Ϯ��$n" HIY "��\n" NOR;

        ap = attack_power(me, "cuff") +
             me->query_con() * 20;

        dp = defense_power(target, "parry") +
             target->query_con() * 20;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");
                damage+= query("jiali", me);
                addn("neili", -260, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
                                           HIR "ֻ��$P" HIR "��һȭ��$p" HIR
                                           "���˳�ȥ�����ص�ˤ�ڵ��ϣ���Ѫ��ֹ��\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "����$p" HIC "�����мܣ�Ӳ�����ĵ�����$P"
                       HIC "��һ�С�\n"NOR;
                addn("neili", -120, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
