#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "�޿ײ���" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "whip" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" +name()+ "��\n");

        if ((int)me->query_skill("sanwu-shou", 1) < 140)
                return notify_fail("�����������ֹ���죬����ʩչ" +name()+ "��\n");

        if (me->query_skill_mapped("whip") != "sanwu-shou")
                return notify_fail("��û�м������������֣�����ʩչ" +name()+ "��\n");

        if (me->query_skill("force") < 180)
                return notify_fail("����ڹ���Ϊ����������ʩչ" +name()+ "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" +name()+ "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "whip");
        dp = defense_power(target, "parry");

        msg = HIY "\n$N" HIY "һ����Х���ھ����ǣ�ʩ�����С�" HIW "�޿�"
              "����" HIY "������" + weapon->name() + HIY "�������죬��"
              "��������\n$N" HIY "��Ȼ�ڿն��𣬻��������е�" + weapon->name() +
              HIY "�����ֱ�£�ӿ��$n" HIY "��\n" NOR;
        message_combatd(msg, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");

                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "����$N" HIR "������飬���ư��磬"
                                           "$n" HIR "������΢һ�����ҽ�һ������"
                                           "ʱ��Ѫ���ܡ�\n" NOR);

                me->start_busy(2);
                addn("neili", -220, me);
        } else
        {
                msg = CYN "$n" CYN "��$N" CYN "����Ϯ��������"
                      "��ӯ��ֻ�����һ�ݣ��Ŷ����һ�ޡ�\n" NOR;

                me->start_busy(3);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);
        return 1;
}
