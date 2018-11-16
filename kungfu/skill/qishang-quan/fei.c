// This program is a part of NITAN MudLIB
// fei.c ���Ƿ���

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "���Ƿ���" NOR; }

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

        if ((int)me->query_skill("qishang-quan", 1) < 160)
                return notify_fail("�������ȭ������죬�޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force", 1) < 160)
                return notify_fail("����ڹ���Ϊ���������޷�ʩչ" + name() + "\n");

        if (query("max_neili", me) < 2200)
                return notify_fail("��������Ϊ���㣬�޷�ʩչ" + name() + "\n");

        if ((int)query("neili", me) < 350)
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("��û��׼��ʹ������ȭ���޷�ʩչ" + name() + "��\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "\n$N" HIY "����һ���𣬽���������˫ȭ֮�ϣ�ʩ�����С�" HIR "���Ƿ���" HIY
              "������ȭƽƽһȭֱ����\n������ͨһȭ֮���̺��������������ȭδ������������Ȼ"
              "��Ϯ��$n" HIY "��\n" NOR;

        ap = attack_power(me, "cuff") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");
                damage+= query("jiali", me);

                addn("neili", -320, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
                                           HIR "ֻ�����顱��һ����$N" HIR "һȭ���ô���$n" HIR "��"
                                           "�ڣ�$n" HIR "�ֽ�һ�����³�һ����Ѫ��\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "����$p" HIC "�����мܣ�Ӳ�����ĵ�����$P"
                       HIC "��һ�С�\n"NOR;
                addn("neili", -180, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
