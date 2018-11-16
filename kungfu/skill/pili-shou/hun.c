// This program is a part of NITAN MudLIB
// hun.c ��ػ�Ԫ

#include <ansi.h>
#include <combat.h>

string name() { return HIW "��ػ�Ԫ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        skill = me->query_skill("pili-shou", 1);

        if (skill < 140)
                return notify_fail("��Ļ�Ԫ�����ֵȼ�����, ����ʩչ" + name() + "��\n");

        if (me->query_skill("force", 1) < 160)
                return notify_fail("���ڹ���Ϊ�������޷�ʩչ" + name() + "��\n");

        if (query("max_neili", me) < 2400)
                return notify_fail("��������Ϊ���㣬�޷�ʩչ" + name() + "��\n");

        if (query("neili", me) < 340)
                return notify_fail("��������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("hand") != "pili-shou")
                return notify_fail("��û��׼��ʹ�û�Ԫ�����֣��޷�ʩչ" + name() + "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "ŭ��һ����ʩ�����С�" HIW "��ػ�Ԫ" HIC "����˫�ƽ���"
              "Ϯ��$n" HIC "���Ʒ��������������з���֮�ơ�\n" NOR;

        ap = attack_power(me, "hand") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -300, me);
                damage = damage_power(me, "hand");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "ֻ������ǰһ���ʹ�����ۡ���һ"
                                           "�����һ����Ѫ��\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -200, me);
                msg += CYN "ֻ��$n" CYN "���Ų�æ������һ�������"
                       "��$N" CYN "�ı�ɱһ����\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
