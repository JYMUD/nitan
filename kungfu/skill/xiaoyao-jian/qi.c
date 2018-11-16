#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "�潣��" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;

        me = this_player();

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = query_temp("weapon", me))
           || (string)query("skill_type", weapon) != "sword")
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("xiaoyao-jian", 1) < 160)
                return notify_fail("����ң����������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "xiaoyao-jian")
                return notify_fail("��û�м�����ң����������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force", 1) < 160)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if (query("max_neili", me) < 2200)
                return notify_fail("��������Ϊ���㣬����ʩչ" + name() + "��\n");

        if ((int)query("neili", me) < 350)
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();

        msg = HIW "\n$N" HIW "��" + wn + HIW "бָ���գ��͵ط���Ծ��"
              + wn + HIW "������ң�Ʈ����������Ȼ���ƿճ��죬" + wn + HIW
              "ֱָ��$n" HIW "�ʺ�\n��������ң����֮��" HIG "�潣��" HIW "����"
              "���������о��棬�����ޱȡ�" NOR;

        message_combatd(msg, me, target);

        ap = attack_power(me, "sword") + me->query_skill("dodge");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 78,
                                          HIR "$n" HIR "ֻ��һ�����Ӱ��Ϯ����"
                                          "���о������ѣ�����Ѫ�Ѵ�$n�ؿ������\n"
                                          NOR);
                me->start_busy(2 + random(4));
                addn("neili", -300, me);
        } else
        {
                msg = CYN "Ȼ��$n" CYN "�����ֿ죬����һ��"
                      "���$N" CYN "��һ����\n" NOR;

                me->start_busy(2);
                addn("neili", -200, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
