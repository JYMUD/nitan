#include <ansi.h>
#include <combat.h>

string name() { return HIW "�Ƽ���ɽ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("tiexian-quan", 1) < 60)
                return notify_fail("������ȭ��������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("cuff") != "tiexian-quan")
                return notify_fail("��û�м�������ȭ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("cuff") != "tiexian-quan")
                return notify_fail("��û��׼������ȭ��������ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 80)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "parry");

        msg = HIC "\n$N" HIC "��Хһ����ʩ�����С�" HIW "��ɽ��" HIC "����һ\n"
              "ȭ�ӳ����ƿն��죬ֱ��$n" HIC "���ź��ؿڡ�\n" NOR;

        message_combatd(msg, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");

                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                          HIR "$N" HIR "���ּȿ죬��λ���棬$n"
                                          HIR "���ܲ������ƺ�һ������Ȼ��ȭ��\n" NOR);

                addn("neili", -100, me);
                me->start_busy(2);
        } else
        {
                msg = CYN "$n" CYN "���Ų�æ���Կ��죬��$N"
                      CYN "���л�ȥ��\n" NOR;

                addn("neili", -30, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}