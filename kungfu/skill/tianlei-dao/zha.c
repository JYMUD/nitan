#include <ansi.h>
#include <combat.h>

string name() { return HIY "����ը��" NOR; }

inherit F_SSERVER;

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

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("tianlei-dao", 1) < 150)
                return notify_fail("�����׾���������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "tianlei-dao")
                return notify_fail("��û�м������׾���������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();

        msg = HIW "\n$N" HIW "һ��ŭ�ȣ��ھ����ǣ�ʩչ�����С�" HIY "����ը��" HIW
              "������\n" + wn + HIW "�����Ļ���������������ˣ���������һ�㡣" NOR;

        message_combatd(msg, me, target);

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                          HIR "$n" HIR "��$N" HIR "�������ͣ���"
                                          "����˸��������������һ����һ����Ѫ"
                                          "��ӿ������\n" NOR);
                me->start_busy(2 + random(2));
                addn("neili", -240, me);
        } else
        {
                msg = CYN "Ȼ��$n" CYN "�Կ��ƿ죬����"
                      "һ����������С�\n" NOR;

                me->start_busy(2);
                addn("neili", -180, me);
        }
        message_combatd(msg, me, target);

        return 1;
}


