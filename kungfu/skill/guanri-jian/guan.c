#include <ansi.h>
#include <combat.h>

string name() { return HIW "����¯��" HIR "��" HIW "���" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int i, count;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" +name()+ "��\n");

        if ((int)me->query_skill("guanri-jian", 1) < 280)
                return notify_fail("����ս���������죬����ʩչ" +name()+ "��\n");

        if (me->query_skill_mapped("sword") != "guanri-jian")
                return notify_fail("��û�м������ս���������ʩչ" +name()+ "��\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("���������Ϊ����������ʩչ" +name()+ "��\n");

        if( query("neili", me)<800 )
                return notify_fail("�����ڵ��������㣬����ʩչ" +name()+ "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "ʩ�����ս���֮��" HIW "����¯��"
              HIR "��" HIW "���" NOR + WHT "��������������ע"
              "��" + weapon->name() + WHT "����ֱ��\n$n" WHT
              "��ȥ����ʱ����ױ��ǣ�����������������ܿ�����"
              "�Ʒ���һ�㡣\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        me->start_busy(3);
        addn("neili", -600, me);

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           (: final, me, target, damage :));
        } else
        {
                me->start_busy(2);
                msg += CYN "����$n" CYN "������$N" CYN "����ͼ��бԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        count = me->query_skill("sword");
        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);

        message_combatd(WHT "������$N" WHT "һ����Ц���������ǰԾ��"
                        "������" + weapon->name() + WHT "����ৡ�"
                        "�����Ž���\n" NOR, me, target);

        for (i = 0; i < 9; i++)
              {
                       if (! me->is_fighting(target))
                               break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);

        return 1;
}

string final(object me, object target, int damage)
{
        int lvl = me->query_skill("guanri-jian", 1);

        target->affect_by("zhurong_jian",
                ([ "level"    : lvl + random(lvl),
                   "id":query("id", me),
                   "duration" : lvl / 50 + random(lvl / 20) ]));

        return  HIR "ֻ��$p" HIR "һ���Һ���������Ѫ���������"
                "��������һ���һ��յ��������졣\n" NOR;
}
