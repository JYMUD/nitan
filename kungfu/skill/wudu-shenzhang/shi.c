#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "������" NOR; }

string final(object me, object target, int damage);

int perform(object me, object target)
{
        string msg;
        int damage;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ������������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("wudu-shenzhang", 1) < 150)
                return notify_fail("����嶾���Ʋ�����죬����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "wudu-shenzhang")
                return notify_fail("������û��׼���嶾���ƣ�����ʩչ" + name() + "��\n");

        if( query("neili", me)<120 )
                return notify_fail("�����������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "��������������˫��֮�䣬ֻ��˫��΢΢�����Ϲ⣬��"
              "������$n��\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)
        {

                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60,
                                          (: final, me, target, damage :));

                me->start_busy(2);
        } else
        {
                msg += CYN "����$p" CYN "�����ֿ죬����һ��$P"
                       CYN "�Ѷ��$N���С�\n" NOR;
                me->start_busy(3);
                target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        int ap, dp;

        ap = me->query_skill("strike");
        dp = target->query_skill("force");

        target->affect_by("wudu_shenzhang",
                (["level":query("jiali", me)+random(query("jiali", me)),
                   "id":query("id", me),
                   "duration" : ap / 70 + random(ap / 30) ]));

        target->receive_wound("jing", damage / 5, me);

        return  HIR "ֻ��$n" HIR "��$N" HIR "һ������"
                "�����˼�����ȴ����ɫ��΢΢���ڡ�\n" NOR;

}